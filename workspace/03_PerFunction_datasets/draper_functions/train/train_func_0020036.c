endin_istag( char *buf )
{
	const char others[]="!@#$^&*()+=?[~>";
	if ( buf[0]!='%' ) return 0;
	if ( buf[2]!=' ' ) return 0;
	if ( isalpha( buf[1] ) ) return 1;
	if ( isdigit( buf[1] ) ) return 1;
	if ( strchr( others, buf[1] ) ) return 1;
	return 0;
}
