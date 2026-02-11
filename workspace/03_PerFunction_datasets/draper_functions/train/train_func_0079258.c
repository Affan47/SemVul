channel( int i, int type )
{
	int out = 2;
	if ( !type )
	{
		out = i % 5;
		if ( out > 2 )
			out = 2;
	}
	else if ( !(type & noise_type) && (type & type_index_mask) % 3 != 0 )
	{
		out = type & 1;
	}
	return chan_types [out];
}
