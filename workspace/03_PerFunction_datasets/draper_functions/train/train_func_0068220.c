vim_strup(p)
    char_u	*p;
{
    char_u  *p2;
    int	    c;

    if (p != NULL)
    {
	p2 = p;
	while ((c = *p2) != NUL)
#ifdef EBCDIC
	    *p2++ = isalpha(c) ? toupper(c) : c;
#else
	    *p2++ = (c < 'a' || c > 'z') ? c : (c - 0x20);
#endif
    }
}
