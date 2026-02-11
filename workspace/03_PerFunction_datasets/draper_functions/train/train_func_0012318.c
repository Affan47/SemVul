toPatternTime(UnicodeString& result, UErrorCode& status) const
{
    if (!U_FAILURE(status)) {
        result.remove();
        result.setTo(fTimePattern);
    }
    return result;
}
