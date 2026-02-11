concat_esc(gap, text, what)
    garray_T	*gap;
    char_u	*text;
    int		what;
{
    while (*text != NUL)
    {
#ifdef FEAT_MBYTE
	int l = (*mb_ptr2len)(text);

	if (l > 1)
	{
	    while (--l >= 0)
		ga_append(gap, *text++);
	    continue;
	}
#endif
	if (*text == what)
	    ga_append(gap, '\\');
	ga_append(gap, *text);
	++text;
    }
}
