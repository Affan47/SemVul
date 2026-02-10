append_char(char **pp, char *e, char c)
{
	if (*pp < e)
		*(*pp)++ = c;
}
