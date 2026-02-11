parseAsciiOffsetFields(const UnicodeString& text, ParsePosition& pos, UChar sep, OffsetFields minFields, OffsetFields maxFields) {
    int32_t start = pos.getIndex();
    int32_t fieldVal[] = {0, 0, 0};
    int32_t fieldLen[] = {0, -1, -1};
    for (int32_t idx = start, fieldIdx = 0; idx < text.length() && fieldIdx <= maxFields; idx++) {
        UChar c = text.charAt(idx);
        if (c == sep) {
            if (fieldIdx == 0) {
                if (fieldLen[0] == 0) {

                    break;
                }

            } else {
                if (fieldLen[fieldIdx] != -1) {

                    break;
                }
                fieldLen[fieldIdx] = 0;
            }
            continue;
        } else if (fieldLen[fieldIdx] == -1) {

            break;
        }
        int32_t digit = DIGIT_VAL(c);
        if (digit < 0) {

            break;
        }
        fieldVal[fieldIdx] = fieldVal[fieldIdx] * 10 + digit;
        fieldLen[fieldIdx]++;
        if (fieldLen[fieldIdx] >= 2) {

            fieldIdx++;
        }
    }

    int32_t offset = 0;
    int32_t parsedLen = 0;
    int32_t parsedFields = -1;
    do {

        if (fieldLen[0] == 0) {
            break;
        }
        if (fieldVal[0] > MAX_OFFSET_HOUR) {
            offset = (fieldVal[0] / 10) * MILLIS_PER_HOUR;
            parsedFields = FIELDS_H;
            parsedLen = 1;
            break;
        }
        offset = fieldVal[0] * MILLIS_PER_HOUR;
        parsedLen = fieldLen[0];
        parsedFields = FIELDS_H;


        if (fieldLen[1] != 2 || fieldVal[1] > MAX_OFFSET_MINUTE) {
            break;
        }
        offset += fieldVal[1] * MILLIS_PER_MINUTE;
        parsedLen += (1 + fieldLen[1]);
        parsedFields = FIELDS_HM;


        if (fieldLen[2] != 2 || fieldVal[2] > MAX_OFFSET_SECOND) {
            break;
        }
        offset += fieldVal[2] * MILLIS_PER_SECOND;
        parsedLen += (1 + fieldLen[2]);
        parsedFields = FIELDS_HMS;
    } while (false);

    if (parsedFields < minFields) {
        pos.setErrorIndex(start);
        return 0;
    }

    pos.setIndex(start + parsedLen);
    return offset;
}
