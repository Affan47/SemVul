reset_fcode_ranges( void)
{
    if ( ranges_exist )
    {
	while ( current_fc_range != NULL )
	{
	    current_fc_range = first_fc_range->fcr_next;
	    free( first_fc_range->fcr_infile);
	    free( first_fc_range);
	    first_fc_range = current_fc_range;
	}
	ranges_exist = FALSE;
    }else{
	if ( first_fcr_infile != NULL )
	{
	    if ( strcmp( first_fcr_infile, iname) != 0 )
	    {
		free( first_fcr_infile);
		first_fcr_infile = NULL;
	    }
	}
    }

    changes_listed    = FALSE;
    range_start       = FCODE_START;
    range_end         = 0;

    if ( first_fcr_infile == NULL )
    {
	first_fcr_infile = strdup( iname);
    }
    first_fcr_linenum = lineno;
    nextfcode         = FCODE_START;
}
