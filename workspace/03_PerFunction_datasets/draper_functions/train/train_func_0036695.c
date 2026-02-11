matchGrouping(UChar32 groupingChar,
                            UBool sawGrouping, UChar32 sawGroupingChar,
                             const UnicodeSet *sset,
                             UChar32 decimalChar, const UnicodeSet *decimalSet,
                             UChar32 schar) {
    if(sawGrouping) {
        return schar==sawGroupingChar;
    } else if(schar==groupingChar) {
        return TRUE;
    } else if(sset!=NULL) {
        return sset->contains(schar) &&
           ((decimalSet==NULL) || !decimalSet->contains(schar));
    } else {
        return FALSE;
    }
}
