hasSameRules(const TimeZone& other) const
{
    if (this == &other) return TRUE;
    if (other.getDynamicClassID() != SimpleTimeZone::getStaticClassID()) return FALSE;
    SimpleTimeZone *that = (SimpleTimeZone*)&other;
    return rawOffset     == that->rawOffset &&
        useDaylight     == that->useDaylight &&
        (!useDaylight

         || (dstSavings     == that->dstSavings &&
             startMode      == that->startMode &&
             startMonth     == that->startMonth &&
             startDay       == that->startDay &&
             startDayOfWeek == that->startDayOfWeek &&
             startTime      == that->startTime &&
             startTimeMode  == that->startTimeMode &&
             endMode        == that->endMode &&
             endMonth       == that->endMonth &&
             endDay         == that->endDay &&
             endDayOfWeek   == that->endDayOfWeek &&
             endTime        == that->endTime &&
             endTimeMode    == that->endTimeMode &&
             startYear      == that->startYear));
}
