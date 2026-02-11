fieldDifference(UDate targetMs, UCalendarDateFields field, UErrorCode& ec) {
    if (U_FAILURE(ec)) return 0;
    int32_t min = 0;
    double startMs = getTimeInMillis(ec);


    if (startMs < targetMs) {
        int32_t max = 1;

        while (U_SUCCESS(ec)) {
            setTimeInMillis(startMs, ec);
            add(field, max, ec);
            double ms = getTimeInMillis(ec);
            if (ms == targetMs) {
                return max;
            } else if (ms > targetMs) {
                break;
            } else {
                min = max;
                max <<= 1;
                if (max < 0) {

#if defined (U_DEBUG_CAL)
                    fprintf(stderr, "%s:%d: ILLEGAL ARG because field %s's max too large for int32_t\n",
                        __FILE__, __LINE__, fldName(field));
#endif
                    ec = U_ILLEGAL_ARGUMENT_ERROR;
                }
            }
        }

        while ((max - min) > 1 && U_SUCCESS(ec)) {
            int32_t t = (min + max) / 2;
            setTimeInMillis(startMs, ec);
            add(field, t, ec);
            double ms = getTimeInMillis(ec);
            if (ms == targetMs) {
                return t;
            } else if (ms > targetMs) {
                max = t;
            } else {
                min = t;
            }
        }
    } else if (startMs > targetMs) {
        int32_t max = -1;

        while (U_SUCCESS(ec)) {
            setTimeInMillis(startMs, ec);
            add(field, max, ec);
            double ms = getTimeInMillis(ec);
            if (ms == targetMs) {
                return max;
            } else if (ms < targetMs) {
                break;
            } else {
                min = max;
                max <<= 1;
                if (max == 0) {

#if defined (U_DEBUG_CAL)
                    fprintf(stderr, "%s:%d: ILLEGAL ARG because field %s's max too large for int32_t\n",
                        __FILE__, __LINE__, fldName(field));
#endif
                    ec = U_ILLEGAL_ARGUMENT_ERROR;
                }
            }
        }

        while ((min - max) > 1 && U_SUCCESS(ec)) {
            int32_t t = (min + max) / 2;
            setTimeInMillis(startMs, ec);
            add(field, t, ec);
            double ms = getTimeInMillis(ec);
            if (ms == targetMs) {
                return t;
            } else if (ms < targetMs) {
                max = t;
            } else {
                min = t;
            }
        }
    }

    setTimeInMillis(startMs, ec);
    add(field, min, ec);


    if(U_FAILURE(ec)) {
        return 0;
    }
    return min;
}
