spell_iswordp_nmw(p)
    char_u	*p;
{
#ifdef FEAT_MBYTE
    int		c;

    if (has_mbyte)
    {
	c = mb_ptr2char(p);
	if (c > 255)
	    return spell_mb_isword_class(mb_get_class(p));
	return spelltab.st_isw[c];
    }
#endif
    return spelltab.st_isw[*p];
}
