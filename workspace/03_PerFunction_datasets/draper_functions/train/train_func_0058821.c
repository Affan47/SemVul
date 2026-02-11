mkd_string_to_anchor(char *s, int len, void(*outchar)(int,void*), void *out)
{
    unsigned char c;

    for ( ; len-- > 0; ) {
	c = *s++;
	if ( c == ' ' || c == '&' || c == '<' || c == '"' )
	    (*outchar)('+', out);
	else if ( isalnum(c) || ispunct(c) || (c & 0x80) )
	    (*outchar)(c, out);
	else
	    (*outchar)('~',out);
    }
}
