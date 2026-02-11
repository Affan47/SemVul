setMonths(const UnicodeString* monthsArray, int32_t count, DtContextType context, DtWidthType width)
{


    switch (context) {
    case FORMAT :
        switch (width) {
        case WIDE :
            if (fMonths)
                delete[] fMonths;
            fMonths = newUnicodeStringArray(count);
            uprv_arrayCopy( monthsArray,fMonths,count);
            fMonthsCount = count;
            break;
        case ABBREVIATED :
            if (fShortMonths)
                delete[] fShortMonths;
            fShortMonths = newUnicodeStringArray(count);
            uprv_arrayCopy( monthsArray,fShortMonths,count);
            fShortMonthsCount = count;
            break;
        case NARROW :
            if (fNarrowMonths)
                delete[] fNarrowMonths;
            fNarrowMonths = newUnicodeStringArray(count);
            uprv_arrayCopy( monthsArray,fNarrowMonths,count);
            fNarrowMonthsCount = count;
            break;
        case DT_WIDTH_COUNT :
            break;
        }
        break;
    case STANDALONE :
        switch (width) {
        case WIDE :
            if (fStandaloneMonths)
                delete[] fStandaloneMonths;
            fStandaloneMonths = newUnicodeStringArray(count);
            uprv_arrayCopy( monthsArray,fStandaloneMonths,count);
            fStandaloneMonthsCount = count;
            break;
        case ABBREVIATED :
            if (fStandaloneShortMonths)
                delete[] fStandaloneShortMonths;
            fStandaloneShortMonths = newUnicodeStringArray(count);
            uprv_arrayCopy( monthsArray,fStandaloneShortMonths,count);
            fStandaloneShortMonthsCount = count;
            break;
        case NARROW :
           if (fStandaloneNarrowMonths)
                delete[] fStandaloneNarrowMonths;
            fStandaloneNarrowMonths = newUnicodeStringArray(count);
            uprv_arrayCopy( monthsArray,fStandaloneNarrowMonths,count);
            fStandaloneNarrowMonthsCount = count;
            break;
        case DT_WIDTH_COUNT :
            break;
        }
        break;
    case DT_CONTEXT_COUNT :
        break;
    }
}
