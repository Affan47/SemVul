clip_yank_selection(type, str, len, cbd)
    int		type;
    char_u	*str;
    long	len;
    VimClipboard *cbd;
{
    struct yankreg *y_ptr;

    if (cbd == &clip_plus)
	y_ptr = &y_regs[PLUS_REGISTER];
    else
	y_ptr = &y_regs[STAR_REGISTER];

    clip_free_selection(cbd);

    str_to_reg(y_ptr, type, str, len, 0L);
}
