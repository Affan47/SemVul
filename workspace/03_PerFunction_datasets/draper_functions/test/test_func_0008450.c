getActualMaximum(UCalendarDateFields field, UErrorCode& status) const
{


    switch (field) {

    case UCAL_YEAR:


        {
            if(U_FAILURE(status)) return 0;
            Calendar *cal = clone();
            if(!cal) {
                status = U_MEMORY_ALLOCATION_ERROR;
                return 0;
            }

            cal->setLenient(TRUE);

            int32_t era = cal->get(UCAL_ERA, status);
            UDate d = cal->getTime(status);


            int32_t lowGood = kGregorianCalendarLimits[UCAL_YEAR][1];
            int32_t highBad = kGregorianCalendarLimits[UCAL_YEAR][2]+1;
            while ((lowGood + 1) < highBad) {
                int32_t y = (lowGood + highBad) / 2;
                cal->set(UCAL_YEAR, y);
                if (cal->get(UCAL_YEAR, status) == y && cal->get(UCAL_ERA, status) == era) {
                    lowGood = y;
                } else {
                    highBad = y;
                    cal->setTime(d, status);
                }
            }

            delete cal;
            return lowGood;
        }

    default:
        return Calendar::getActualMaximum(field,status);
    }
}
