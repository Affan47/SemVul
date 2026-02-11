sec_lower_string(char *s)
{
    if ( s == NULL ) {
	return;
    }

    while ( *s ) {
	*s = PORT_Tolower(*s);
	s++;
    }

    return;
}
