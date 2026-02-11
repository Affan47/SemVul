handleComputeFields(int32_t julianDay, UErrorCode &status) {
    int32_t year, month, dayOfMonth, dayOfYear;
    UDate startDate;
    int32_t days = julianDay - 1948440;

    if (civil == CIVIL) {

        year  = (int)ClockMath::floorDivide( (double)(30 * days + 10646) , 10631.0 );
        month = (int32_t)uprv_ceil((days - 29 - yearStart(year)) / 29.5 );
        month = month<11?month:11;
        startDate = monthStart(year, month);
    } else {

        int32_t months = (int32_t)uprv_floor((double)days / CalendarAstronomer::SYNODIC_MONTH);

        startDate = uprv_floor(months * CalendarAstronomer::SYNODIC_MONTH);

        double age = moonAge(internalGetTime(), status);
        if (U_FAILURE(status)) {
        	status = U_MEMORY_ALLOCATION_ERROR;
        	return;
        }
        if ( days - startDate >= 25 && age > 0) {

            months++;
        }


        while ((startDate = trueMonthStart(months)) > days) {

            months--;
        }

        year = months / 12 + 1;
        month = months % 12;
    }

    dayOfMonth = (days - monthStart(year, month)) + 1;


    dayOfYear = (days - monthStart(year, 0) + 1);

    internalSet(UCAL_ERA, 0);
    internalSet(UCAL_YEAR, year);
    internalSet(UCAL_EXTENDED_YEAR, year);
    internalSet(UCAL_MONTH, month);
    internalSet(UCAL_DAY_OF_MONTH, dayOfMonth);
    internalSet(UCAL_DAY_OF_YEAR, dayOfYear);
}
