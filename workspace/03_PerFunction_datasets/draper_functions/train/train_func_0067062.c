parseGlobalFilter(const UnicodeString& id, int32_t& pos,
                                                      int32_t dir,
                                                      int32_t& withParens,
                                                      UnicodeString* canonID) {
    UnicodeSet* filter = NULL;
    int32_t start = pos;

    if (withParens == -1) {
        withParens = ICU_Utility::parseChar(id, pos, OPEN_REV) ? 1 : 0;
    } else if (withParens == 1) {
        if (!ICU_Utility::parseChar(id, pos, OPEN_REV)) {
            pos = start;
            return NULL;
        }
    }

    ICU_Utility::skipWhitespace(id, pos, TRUE);

    if (UnicodeSet::resemblesPattern(id, pos)) {
        ParsePosition ppos(pos);
        UErrorCode ec = U_ZERO_ERROR;
        filter = new UnicodeSet(id, ppos, USET_IGNORE_SPACE, NULL, ec);

        if (filter == 0) {
            pos = start;
            return 0;
        }
        if (U_FAILURE(ec)) {
            delete filter;
            pos = start;
            return NULL;
        }

        UnicodeString pattern;
        id.extractBetween(pos, ppos.getIndex(), pattern);
        pos = ppos.getIndex();

        if (withParens == 1 && !ICU_Utility::parseChar(id, pos, CLOSE_REV)) {
            pos = start;
            return NULL;
        }


        if (canonID != NULL) {
            if (dir == FORWARD) {
                if (withParens == 1) {
                    pattern.insert(0, OPEN_REV);
                    pattern.append(CLOSE_REV);
                }
                canonID->append(pattern).append(ID_DELIM);
            } else {
                if (withParens == 0) {
                    pattern.insert(0, OPEN_REV);
                    pattern.append(CLOSE_REV);
                }
                canonID->insert(0, pattern);
                canonID->insert(pattern.length(), ID_DELIM);
            }
        }
    }

    return filter;
}
