operator==(const DateTimePatternGenerator& other) const {
    if (this == &other) {
        return TRUE;
    }
    if ((pLocale==other.pLocale) && (patternMap->equals(*other.patternMap)) &&
        (dateTimeFormat==other.dateTimeFormat) && (decimal==other.decimal)) {
        for ( int32_t i=0 ; i<UDATPG_FIELD_COUNT; ++i ) {
           if ((appendItemFormats[i] != other.appendItemFormats[i]) ||
               (appendItemNames[i] != other.appendItemNames[i]) ) {
               return FALSE;
           }
        }
        return TRUE;
    }
    else {
        return FALSE;
    }
}
