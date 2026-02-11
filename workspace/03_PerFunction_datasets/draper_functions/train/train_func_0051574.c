status_match_len(xp, s)
    expand_T	*xp;
    char_u	*s;
{
    int	len = 0;

#ifdef FEAT_MENU
    int emenu = (xp->xp_context == EXPAND_MENUS
	    || xp->xp_context == EXPAND_MENUNAMES);


    if (emenu && menu_is_separator(s))
	return 1;
#endif

    while (*s != NUL)
    {
	s += skip_status_match_char(xp, s);
	len += ptr2cells(s);
	mb_ptr_adv(s);
    }

    return len;
}
