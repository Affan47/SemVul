fixup_board_name( char *name )
{
	while( ( name = strchr( name, '/' ) ) )
	{
		if( name )
		{
			*name = '-';
			name++;
		}
	}
}
