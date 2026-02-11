get_name( void )
{
	get_token();
	if( flag ) fixate_literal_string();
	else *--sp = 0;
}
