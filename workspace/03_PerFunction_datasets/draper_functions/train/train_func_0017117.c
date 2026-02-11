unicode_to_ebcdic_ge(ucs4_t u, Boolean *ge)
{
    ebc_t e;

    *ge = False;
    e = unicode_to_ebcdic(u);
    if (e)
	return e;


    for (e = 0x70; e <= 0xfe; e++) {
	if ((ucs4_t)apl_to_unicode(e, EUO_NONE) == u) {
	    *ge = True;
	    return e;
	}
    }

    return 0;
}
