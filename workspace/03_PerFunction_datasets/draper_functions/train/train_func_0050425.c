get_locales(xp, idx)
    expand_T	*xp UNUSED;
    int		idx;
{
    init_locales();
    if (locales == NULL)
	return NULL;
    return locales[idx];
}
