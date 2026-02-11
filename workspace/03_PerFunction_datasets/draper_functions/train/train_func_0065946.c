Perl_bytes_from_utf8(pTHX_ const U8 *s, STRLEN *len, bool *is_utf8)
{
    U8 *d;
    const U8 *start = s;
    const U8 *send;
    I32 count = 0;

    PERL_ARGS_ASSERT_BYTES_FROM_UTF8;

    PERL_UNUSED_CONTEXT;
    if (!*is_utf8)
        return (U8 *)start;


    for (send = s + *len; s < send;) {
        U8 c = *s++;
	if (!UTF8_IS_INVARIANT(c)) {
	    if (UTF8_IS_DOWNGRADEABLE_START(c) && s < send &&
                (c = *s++) && UTF8_IS_CONTINUATION(c))
		count++;
	    else
                return (U8 *)start;
	}
    }

    *is_utf8 = FALSE;

    Newx(d, (*len) - count + 1, U8);
    s = start; start = d;
    while (s < send) {
	U8 c = *s++;
	if (!UTF8_IS_INVARIANT(c)) {

	    c = UNI_TO_NATIVE(TWO_BYTE_UTF8_TO_UNI(c, *s++));
	}
	*d++ = c;
    }
    *d = '\0';
    *len = d - start;
    return (U8 *)start;
}
