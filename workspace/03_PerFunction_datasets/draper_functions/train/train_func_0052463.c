print_string( cell * s )
{
	int len = *s++;

	while( len-- ) { *--sp = *s++; put(); }
}
