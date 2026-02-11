get_menu_names(xp, idx)
    expand_T	*xp UNUSED;
    int		idx;
{
    static vimmenu_T	*menu = NULL;
#define TBUFFER_LEN 256
    static char_u	tbuffer[TBUFFER_LEN];
    char_u		*str;
#ifdef FEAT_MULTI_LANG
    static  int		should_advance = FALSE;
#endif

    if (idx == 0)
    {
	menu = expand_menu;
#ifdef FEAT_MULTI_LANG
	should_advance = FALSE;
#endif
    }


    while (menu != NULL
	    && (   menu_is_hidden(menu->dname)
		|| (expand_emenu && menu_is_separator(menu->dname))
		|| menu_is_tearoff(menu->dname)
#ifndef FEAT_BROWSE
		|| menu->dname[STRLEN(menu->dname) - 1] == '.'
#endif
	       ))
	menu = menu->next;

    if (menu == NULL)
	return NULL;

    if (menu->modes & expand_modes)
    {
	if (menu->children != NULL)
	{
#ifdef FEAT_MULTI_LANG
	    if (should_advance)
		vim_strncpy(tbuffer, menu->en_dname, TBUFFER_LEN - 2);
	    else
	    {
#endif
		vim_strncpy(tbuffer, menu->dname,  TBUFFER_LEN - 2);
#ifdef FEAT_MULTI_LANG
		if (menu->en_dname == NULL)
		    should_advance = TRUE;
	    }
#endif


	    STRCAT(tbuffer, "\001");
	    str = tbuffer;
	}
	else
#ifdef FEAT_MULTI_LANG
	{
	    if (should_advance)
		str = menu->en_dname;
	    else
	    {
#endif
		str = menu->dname;
#ifdef FEAT_MULTI_LANG
		if (menu->en_dname == NULL)
		    should_advance = TRUE;
	    }
	}
#endif
    }
    else
	str = (char_u *)"";

#ifdef FEAT_MULTI_LANG
    if (should_advance)
#endif

	menu = menu->next;

#ifdef FEAT_MULTI_LANG
    should_advance = !should_advance;
#endif

    return str;
}
