set(UCalendarDateFields field, int32_t value)
{
    if (fAreFieldsVirtuallySet) {
        UErrorCode ec = U_ZERO_ERROR;
        computeFields(ec);
    }
    fFields[field]     = value;
    fStamp[field]     = fNextStamp++;
    fIsSet[field]     = TRUE;
    fIsTimeSet = fAreFieldsSet = fAreFieldsVirtuallySet = FALSE;
}
