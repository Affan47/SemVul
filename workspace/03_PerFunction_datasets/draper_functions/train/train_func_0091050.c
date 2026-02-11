split(const UnicodeString &input,
        UnicodeString    dest[],
        int32_t          destCapacity,
        UErrorCode       &status) const
{
    if (U_FAILURE(status)) {
        return 0;
    };

    RegexMatcher  m(this);
    int32_t r = 0;

    if (U_SUCCESS(m.fDeferredStatus)) {
    	r = m.split(input, dest, destCapacity, status);
    }
    return r;
}
