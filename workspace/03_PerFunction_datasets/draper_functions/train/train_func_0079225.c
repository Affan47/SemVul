formatOffsetWithAsciiDigits(int32_t offset, UChar sep, OffsetFields minFields, OffsetFields maxFields, UnicodeString& result) {
    U_ASSERT(maxFields >= minFields);
    U_ASSERT(offset > -MAX_OFFSET && offset < MAX_OFFSET);

    UChar sign = PLUS;
    if (offset < 0) {
        sign = MINUS;
        offset = -offset;
    }
    result.setTo(sign);

    int fields[3];
    fields[0] = offset / MILLIS_PER_HOUR;
    offset = offset % MILLIS_PER_HOUR;
    fields[1] = offset / MILLIS_PER_MINUTE;
    offset = offset % MILLIS_PER_MINUTE;
    fields[2] = offset / MILLIS_PER_SECOND;

    U_ASSERT(fields[0] >= 0 && fields[0] <= MAX_OFFSET_HOUR);
    U_ASSERT(fields[1] >= 0 && fields[1] <= MAX_OFFSET_MINUTE);
    U_ASSERT(fields[2] >= 0 && fields[2] <= MAX_OFFSET_SECOND);

    int32_t lastIdx = maxFields;
    while (lastIdx > minFields) {
        if (fields[lastIdx] != 0) {
            break;
        }
        lastIdx--;
    }

    for (int32_t idx = 0; idx <= lastIdx; idx++) {
        if (sep && idx != 0) {
            result.append(sep);
        }
        result.append((UChar)(0x0030 + fields[idx]/10));
        result.append((UChar)(0x0030 + fields[idx]%10));
    }

    return result;
}
