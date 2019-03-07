#include "TimeUtil.h"
#include "bitset"

namespace Cron {

unsigned int TimeUtil::dayEndOfMonth(unsigned int month, int year)
{
    if(month <= 11)
    {
        unsigned int maxPermonth = 31;
        static const std::bitset<12> MONTH31s{"101011010101"}; //[11 .. <- .. 0 ] the months that have 31 days
        if (1 == month) //Febuary
        {
            if (TimeUtil::isLeapYear(year))
            {
                maxPermonth = 29;
            }
            else
            {
                maxPermonth = 28;
            }
        }
        else if (!MONTH31s.test(month))
        {
            maxPermonth = 30;
        }
        return maxPermonth;
    }
    else
    {
        return 0;
    }
}

std::tm* TimeUtil::localTime()
{
	auto ttNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return std::localtime(&ttNow);
}

int TimeUtil::getWeekDayOf(int year, int mon, int day)
{
    std::tm tmTime = Cron::TimeUtil::createTimeInfo(year, mon, day);
    auto timet = std::mktime(&tmTime);
    auto ptmTime = std::localtime(&timet);
    return ptmTime->tm_wday;
}

bool TimeUtil::isLeapYear(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

tm TimeUtil::createTimeInfo(int year, int month, int mDay, int hour, int min, int sec)
{
    return std::tm {
        sec,        // int tm_sec;
        min,        // int tm_min;
        hour,       // int tm_hour;
        mDay,       // int tm_mday;
        month,      // int tm_mon;
        year,       // int tm_year;
        0,          // int tm_wday;
        0,          // int tm_yday;
        0,          // int tm_isdst;
    };
}

}
