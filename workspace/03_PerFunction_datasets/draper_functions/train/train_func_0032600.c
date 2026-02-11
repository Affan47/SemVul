format(int32_t number,
                              const UnicodeString& ruleSetName,
                              UnicodeString& toAppendTo,
                              FieldPosition& ,
                              UErrorCode& status) const
{

    if (U_SUCCESS(status)) {
        if (ruleSetName.indexOf(gPercentPercent) == 0) {

            status = U_ILLEGAL_ARGUMENT_ERROR;
        } else {
            NFRuleSet *rs = findRuleSet(ruleSetName, status);
            if (rs) {
                rs->format((int64_t)number, toAppendTo, toAppendTo.length());
            }
        }
    }
    return toAppendTo;
}
