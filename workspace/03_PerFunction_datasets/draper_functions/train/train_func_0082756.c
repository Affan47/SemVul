clower (c)
     register int c;
{
	return (Char) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}
