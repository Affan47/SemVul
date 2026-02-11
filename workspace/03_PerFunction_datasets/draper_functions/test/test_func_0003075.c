egg_decode( char *s )
{
	const char	*pin;
	char		*pout;


	pin = pout = s;
	while ( *pin!='\0' ) {
		*pout = egg_char2nibble(*pin++)<<4;
		*pout |= egg_char2nibble(*pin++);
		*pout^= 122;
		pout++;
    }
    *pout= '\0';
}
