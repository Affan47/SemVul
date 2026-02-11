init_charset(void)
{
    int i, j;
    union {char b[2]; short s;} bytes;


    bytes.s = 1;

#if CHAR_SIZE == 8
    InternalCharacterEncoding = CE_unspecified_ascii_superset;
#else
    InternalCharacterEncoding = (bytes.b[0] == 0) ? CE_UTF_16B : CE_UTF_16L;
#endif


    for(i=0; i<8; i++)
    {
	int max = 0x9f;

	for(j=0; j<0xa0; j++)
	    iso_to_unicode[i][j] = j;
	for(j=0xa0; j<0x100; j++)
	{
	    int code = latin_table[i][j-0xa0];
	    iso_to_unicode[i][j] = code;
	    if(code > max) max = code;
	}

	iso_max_val[i] = max;

	if(!(unicode_to_iso[i] = Malloc(max+1)))
	{
	    fprintf(stderr, "Malloc failed in charset initialisation\n");
	    exit(1);
	}

	for(j=0; j<0xa0; j++)
	    unicode_to_iso[i][j] = j;
	for(j=0xa0; j<=max; j++)
	    unicode_to_iso[i][j] = '?';
	for(j=0xa0; j<0x100; j++)
	{
	    int code = latin_table[i][j-0xa0];
	    if(code != -1)
		unicode_to_iso[i][code] = j;
	}
    }
}
