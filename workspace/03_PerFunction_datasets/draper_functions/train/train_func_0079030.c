doParse(void) {
    skipWhitespace();
    if (!checkInc(OPEN_ANGLE)) {
        ERROR("Missing open angle");
    } else {
        VArray array(DeleteFn);
        UBool mightHaveNext = TRUE;
        int32_t requiredLength = -1;
        while (mightHaveNext) {
            mightHaveNext = FALSE;
            UChar** elem = nextArray(requiredLength);
            skipWhitespace();
            UBool haveComma = check(COMMA);
            if (elem) {
                array.add(elem, ec);
                if (haveComma) {
                    inc();
                    mightHaveNext = TRUE;
                }
            } else if (haveComma) {
                ERROR("Unexpected character");
            }
        }

        skipWhitespace();
        if (!checkInc(CLOSE_ANGLE)) {
            if (check(OPEN_ANGLE)) {
                ERROR("Missing comma in outer array");
            } else {
                ERROR("Missing close angle bracket in outer array");
            }
        }

        skipWhitespace();
        if (p != e) {
            ERROR("Extra text after close of localization data");
        }

        array.add(NULL, ec);
        if (U_SUCCESS(ec)) {
            int32_t numLocs = array.length() - 2;
            UChar*** result = (UChar***)array.release();

            return new StringLocalizationInfo(data, result, requiredLength-2, numLocs);
        }
    }

    ERROR("Unknown error");
}
