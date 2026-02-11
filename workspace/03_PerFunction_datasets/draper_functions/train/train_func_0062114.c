calc_header_length( u32 len, int new_ctb )
{
    if( !len )
	return 1;

    if( new_ctb ) {
	if( len < 192 )
	    return 2;
	if( len < 8384 )
	    return 3;
	else
	    return 6;
    }
    if( len < 256 )
	return 2;
    if( len < 65536 )
	return 3;

    return 5;
}
