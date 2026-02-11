load(VTZReader& reader, UErrorCode& status) {
    vtzlines = new UVector(uprv_deleteUObject, uhash_compareUnicodeString, DEFAULT_VTIMEZONE_LINES, status);
    if (U_FAILURE(status)) {
        return;
    }
    UBool eol = FALSE;
    UBool start = FALSE;
    UBool success = FALSE;
    UnicodeString line;

    while (TRUE) {
        UChar ch = reader.read();
        if (ch == 0xFFFF) {

            if (start && line.startsWith(ICAL_END_VTIMEZONE, -1)) {
                vtzlines->addElement(new UnicodeString(line), status);
                if (U_FAILURE(status)) {
                    goto cleanupVtzlines;
                }
                success = TRUE;
            }
            break;
        }
        if (ch == 0x000D) {

            continue;
        }
        if (eol) {
            if (ch != 0x0009 && ch != 0x0020) {

                if (start) {
                    if (line.length() > 0) {
                        vtzlines->addElement(new UnicodeString(line), status);
                        if (U_FAILURE(status)) {
                            goto cleanupVtzlines;
                        }
                    }
                }
                line.remove();
                if (ch != 0x000A) {
                    line.append(ch);
                }
            }
            eol = FALSE;
        } else {
            if (ch == 0x000A) {

                eol = TRUE;
                if (start) {
                    if (line.startsWith(ICAL_END_VTIMEZONE, -1)) {
                        vtzlines->addElement(new UnicodeString(line), status);
                        if (U_FAILURE(status)) {
                            goto cleanupVtzlines;
                        }
                        success = TRUE;
                        break;
                    }
                } else {
                    if (line.startsWith(ICAL_BEGIN_VTIMEZONE, -1)) {
                        vtzlines->addElement(new UnicodeString(line), status);
                        if (U_FAILURE(status)) {
                            goto cleanupVtzlines;
                        }
                        line.remove();
                        start = TRUE;
                        eol = FALSE;
                    }
                }
            } else {
                line.append(ch);
            }
        }
    }
    if (!success) {
        if (U_SUCCESS(status)) {
            status = U_INVALID_STATE_ERROR;
        }
        goto cleanupVtzlines;
    }
    parse(status);
    return;

cleanupVtzlines:
    delete vtzlines;
    vtzlines = NULL;
}
