writeZonePropsByTime(VTZWriter& writer, UBool isDst, const UnicodeString& zonename,
                                int32_t fromOffset, int32_t toOffset, UDate time, UBool withRDATE,
                                UErrorCode& status) const {
    if (U_FAILURE(status)) {
        return;
    }
    beginZoneProps(writer, isDst, zonename, fromOffset, toOffset, time, status);
    if (U_FAILURE(status)) {
        return;
    }
    if (withRDATE) {
        writer.write(ICAL_RDATE);
        writer.write(COLON);
        UnicodeString timestr;
        writer.write(getDateTimeString(time + fromOffset, timestr));
        writer.write(ICAL_NEWLINE);
    }
    endZoneProps(writer, isDst, status);
    if (U_FAILURE(status)) {
        return;
    }
}
