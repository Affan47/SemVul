searchCurrencyName(const CurrencyNameStruct* currencyNames,
                   int32_t total_currency_count,
                   const UChar* text, int32_t textLen,
                   int32_t* maxMatchLen, int32_t* maxMatchIndex) {
    *maxMatchIndex = -1;
    *maxMatchLen = 0;
    int32_t matchIndex = -1;
    int32_t binarySearchBegin = 0;
    int32_t binarySearchEnd = total_currency_count - 1;


    for (int32_t index = 0; index < textLen; ++index) {


        matchIndex = binarySearch(currencyNames, index,
                                  text[index],
                                  &binarySearchBegin, &binarySearchEnd);
        if (binarySearchBegin == -1) {
            break;
        }
        if (matchIndex != -1) {


            *maxMatchLen = index + 1;
            *maxMatchIndex = matchIndex;
        }
        if (binarySearchEnd - binarySearchBegin < LINEAR_SEARCH_THRESHOLD) {

            linearSearch(currencyNames, binarySearchBegin, binarySearchEnd,
                         text, textLen,
                         maxMatchLen, maxMatchIndex);
            break;
        }
    }
    return;
}
