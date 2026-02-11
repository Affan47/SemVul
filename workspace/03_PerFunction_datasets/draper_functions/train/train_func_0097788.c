get_sequence(u8 **walk)
{
    int pv_indx = 0;
    bool retval = FALSE;
    bool ready_to_parse = FALSE;
    char next_ch;
    char pval[3];

#ifdef DEBUG_SCANNER
	printf("%s:%d: debug: hex field:", iname, lineno);
#endif
    pval[2]=0;

    while ( pc < end )
    {
	next_ch = *pc;
	if ( next_ch == ')' )
	{
	    retval = TRUE;
				break;
	}
	if ( hex_remark_escape )
	{
	    if ( next_ch == '\\' )
	    {
		string_remark("string hex-sequence remark");
		continue;
	    }
	}
	if ( isxdigit(next_ch) )
	{
	    pval[pv_indx] = next_ch;
	    if ( pv_indx == 0 )
	    {
		pv_indx++;
	    }else{
		ready_to_parse = TRUE;
	    }
	}else{
	    if ( next_ch == '\n' )  lineno++ ;
	    if ( pv_indx != 0 )
	    {
		pval[1] = 0;
		ready_to_parse = TRUE;
	    }
	}
	if ( ready_to_parse )
	{
	    u8 val = parse_number(pval, NULL, 16);
	    *((*walk)++)=val;
#ifdef DEBUG_SCANNER
		printf(" %02x",val);
#endif
	    pv_indx = 0;
	    ready_to_parse = FALSE;
	}
	pc++;
    }
#ifdef DEBUG_SCANNER
	printf("\n");
#endif
    return ( retval );
}
