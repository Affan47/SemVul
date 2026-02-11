translate_to_zscii (zchar c)
{
    int i;

    if (c == ZC_SINGLE_CLICK)
	return 0xfe;
    if (c == ZC_DOUBLE_CLICK)
	return 0xfd;
    if (c == ZC_MENU_CLICK)
	return 0xfc;

    if (c >= ZC_LATIN1_MIN) {

	if (hx_unicode_table != 0) {

	    zbyte N;
	    int i;

	    LOW_BYTE (hx_unicode_table, N)

	    for (i = 0x9b; i < 0x9b + N; i++) {

		zword addr = hx_unicode_table + 1 + 2 * (i - 0x9b);
		zword unicode;

		LOW_WORD (addr, unicode)

		if (c == unicode)
		    return (zbyte) i;

	    }

	    return '?';

	} else {

	    for (i = 0x9b; i <= 0xdf; i++)
		if (c == zscii_to_latin1[i - 0x9b])
		    return (zbyte) i;

	    return '?';

	}
    }

    if (c == 0)
	c = '?';


    return c;

}
