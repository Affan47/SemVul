popup_mode_name(name, idx)
    char_u	*name;
    int		idx;
{
    char_u	*p;
    int		len = (int)STRLEN(name);

    p = vim_strnsave(name, len + 1);
    if (p != NULL)
    {
	mch_memmove(p + 6, p + 5, (size_t)(len - 4));
	p[5] = menu_mode_chars[idx];
    }
    return p;
}
