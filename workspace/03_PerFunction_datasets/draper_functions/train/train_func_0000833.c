format(int32_t number,
                              UnicodeString& toAppendTo,
                              FieldPosition& ) const
{
    if (defaultRuleSet) {
        int32_t startPos = toAppendTo.length();
        defaultRuleSet->format((int64_t)number, toAppendTo, toAppendTo.length());
        adjustForCapitalizationContext(startPos, toAppendTo);
    }
    return toAppendTo;
}
