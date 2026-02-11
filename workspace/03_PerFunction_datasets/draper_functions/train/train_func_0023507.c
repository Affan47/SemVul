createCustomTimeZone(const UnicodeString& id)
{
    int32_t sign, hour, min, sec;
    if (parseCustomID(id, sign, hour, min, sec)) {
        UnicodeString customID;
        formatCustomID(hour, min, sec, (sign < 0), customID);
        int32_t offset = sign * ((hour * 60 + min) * 60 + sec) * 1000;
        return new SimpleTimeZone(offset, customID);
    }
    return NULL;
}
