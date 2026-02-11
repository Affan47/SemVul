copy_char(from, to, lowercase)
    char_u	*from;
    char_u	*to;
    int		lowercase;
{
#ifdef FEAT_MBYTE
    int		len;
    int		c;

    if (has_mbyte)
    {
	if (lowercase)
	{
	    c = MB_TOLOWER((*mb_ptr2char)(from));
	    return (*mb_char2bytes)(c, to);
	}
	else
	{
	    len = (*mb_ptr2len)(from);
	    mch_memmove(to, from, (size_t)len);
	    return len;
	}
    }
    else
#endif
    {
	if (lowercase)
	    *to = (char_u)TOLOWER_LOC(*from);
	else
	    *to = *from;
	return 1;
    }
}
