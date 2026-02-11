Perl_utf8_hop(pTHX_ const U8 *s, I32 off)
{
    PERL_ARGS_ASSERT_UTF8_HOP;

    PERL_UNUSED_CONTEXT;


    if (off >= 0) {
	while (off--)
	    s += UTF8SKIP(s);
    }
    else {
	while (off++) {
	    s--;
	    while (UTF8_IS_CONTINUATION(*s))
		s--;
	}
    }
    return (U8 *)s;
}
