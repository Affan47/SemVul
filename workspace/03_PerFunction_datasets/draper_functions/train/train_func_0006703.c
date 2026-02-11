toLocalizedPattern(UnicodeString& result,
                                     UErrorCode& status) const
{
    translatePattern(fPattern, result, DateFormatSymbols::getPatternUChars(), fSymbols->fLocalPatternChars, status);
    return result;
}
