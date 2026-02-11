option_is_exist( char opch )
{
	int i;

	for( i = 0 ; i < options.count ; i++ )
	{
		if( options.opt[ i ].opch == opch )
			return options.opt + i;
	}
	return NULL;
}
