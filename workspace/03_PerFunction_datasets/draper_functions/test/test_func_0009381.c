isLeapYear(boost::int32_t year)
{
    return !((year + 1900) % 400) ||
            ( !((year + 1900) % 4) && ((year + 1900) % 100));
}
