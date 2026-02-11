assigning_fcode( void)
{
    if ( nextfcode > FCODE_LIMIT )
    {

	tokenization_error( INFO, "");
	list_fcode_ranges( FALSE);

	tokenization_error( FATAL,
	    "Too many definitions.  "
	    "Assigned FCode exceeds limit "
	    "specified by IEEE-1275.");


    }

    changes_listed = FALSE;

    if ( INVERSE(ranges_exist) )
    {
	range_end = nextfcode;
    }else{
	current_fc_range->fcr_end = nextfcode;


	if ( current_fc_range->fcr_not_lapped )
	{
	    fcode_range_t *found_lap = find_overlap( nextfcode);
	    if ( found_lap != NULL )
	    {
		tokenization_error( TKERROR,
		    "Assigning FCode of 0x%x, "
			"which overlaps the range", nextfcode);
		started_at( found_lap->fcr_infile, found_lap->fcr_linenum);

		current_fc_range->fcr_not_lapped = FALSE;
	    }
	}
    }

}
