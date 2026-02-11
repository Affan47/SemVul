getdigraph(char1, char2, meta_char)
    int	char1;
    int	char2;
    int	meta_char;
{
    int	    retval;

    if (((retval = getexactdigraph(char1, char2, meta_char)) == char2)
	    && (char1 != char2)
	    && ((retval = getexactdigraph(char2, char1, meta_char)) == char1))
	return char2;
    return retval;
}
