isLeapYear(int32_t year) const
{


    return (year >= fGregorianCutoverYear ?
        (((year&0x3) == 0) && ((year%100 != 0) || (year%400 == 0))) :
    ((year&0x3) == 0));
}
