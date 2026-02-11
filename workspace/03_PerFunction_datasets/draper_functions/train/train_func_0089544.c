trueMonthStart(int32_t month) const
{
    UErrorCode status = U_ZERO_ERROR;
    int32_t start = CalendarCache::get(&gMonthCache, month, status);

    if (start==0) {

        UDate origin = HIJRA_MILLIS
            + uprv_floor(month * CalendarAstronomer::SYNODIC_MONTH) * kOneDay;


        double age = moonAge(origin, status);
        if (U_FAILURE(status)) {
            goto trueMonthStartEnd;
        }

        if (age >= 0) {

            do {
                origin -= kOneDay;
                age = moonAge(origin, status);
                if (U_FAILURE(status)) {
                    goto trueMonthStartEnd;
                }
            } while (age >= 0);
        }
        else {

            do {
                origin += kOneDay;
                age = moonAge(origin, status);
                if (U_FAILURE(status)) {
                    goto trueMonthStartEnd;
                }
            } while (age < 0);
        }
        start = (int32_t)ClockMath::floorDivide((origin - HIJRA_MILLIS), (double)kOneDay) + 1;
        CalendarCache::put(&gMonthCache, month, start, status);
    }
trueMonthStartEnd :
    if(U_FAILURE(status)) {
        start = 0;
    }
    return start;
}
