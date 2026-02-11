operator==(const TimeZone& that) const
{
    return getDynamicClassID() == that.getDynamicClassID() &&
        fID == that.fID;
}
