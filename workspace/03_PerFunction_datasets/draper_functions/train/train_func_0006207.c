ccladd( cclp, ch )
int cclp;
int ch;
	{
	int ind, len, newpos, i;

	check_char( ch );

	len = ccllen[cclp];
	ind = cclmap[cclp];


	for ( i = 0; i < len; ++i )
		if ( ccltbl[ind + i] == ch )
			return;

	newpos = ind + len;

	if ( newpos >= current_max_ccl_tbl_size )
		{
		current_max_ccl_tbl_size += MAX_CCL_TBL_SIZE_INCREMENT;

		++num_reallocs;

		ccltbl = reallocate_Character_array( ccltbl,
						current_max_ccl_tbl_size );
		}

	ccllen[cclp] = len + 1;
	ccltbl[newpos] = ch;
	}
