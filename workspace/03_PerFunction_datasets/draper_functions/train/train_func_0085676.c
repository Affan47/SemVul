XpTableVectorNew(  size, tw, do_col )
    int			size;
    XpTableWidget	tw;
    int			do_col;
{
    int			minimize, dontStretch, first_slot, last_slot, slot;
    XpTableLoc  	loc = tw->table.real_layout;
    XpTableVector	vec;

    if ( (XpTableLoc)0  == loc || 0 == size )
	return (XpTableVector)0;

    vec = (XpTableVector) XtCalloc( size+1, sizeof(XpTableVectorRec));


    for (  ;  loc->w  ;  loc++ )
    {
	if ( do_col )
	{
	    minimize	= loc->options & TBL_SM_WIDTH;
	    dontStretch	= loc->options & TBL_LK_WIDTH;
	    first_slot	= loc->col;
	    last_slot	= loc->col + loc->col_span;
	}
	else
	{
	    minimize	= loc->options & TBL_SM_HEIGHT;
	    dontStretch	= loc->options & TBL_LK_HEIGHT;
	    first_slot	= loc->row;
	    last_slot	= loc->row + loc->row_span;
	}

	if ( minimize )
	    for ( slot = first_slot ; slot < last_slot ; slot++ )
		vec[ slot ].options |= TBL_VEC_MINIMIZE;

	if ( dontStretch )
	    for ( slot = first_slot ; slot < last_slot ; slot++ )
		vec[ slot ].options |= TBL_VEC_LOCK;
    }
    XpTableVectorMinimize(  vec, size, tw, do_col );
    return vec;
}
