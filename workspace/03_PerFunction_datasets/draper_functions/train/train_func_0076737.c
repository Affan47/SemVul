show_menus(path_name, modes)
    char_u  *path_name;
    int	    modes;
{
    char_u	*p;
    char_u	*name;
    vimmenu_T	*menu;
    vimmenu_T	*parent = NULL;

    menu = root_menu;
    name = path_name = vim_strsave(path_name);
    if (path_name == NULL)
	return FAIL;


    while (*name)
    {
	p = menu_name_skip(name);
	while (menu != NULL)
	{
	    if (menu_name_equal(name, menu))
	    {

		if (*p != NUL && menu->children == NULL)
		{
		    EMSG(_(e_notsubmenu));
		    vim_free(path_name);
		    return FAIL;
		}
		else if ((menu->modes & modes) == 0x0)
		{
		    EMSG(_(e_othermode));
		    vim_free(path_name);
		    return FAIL;
		}
		break;
	    }
	    menu = menu->next;
	}
	if (menu == NULL)
	{
	    EMSG2(_(e_nomenu), name);
	    vim_free(path_name);
	    return FAIL;
	}
	name = p;
	parent = menu;
	menu = menu->children;
    }


    MSG_PUTS_TITLE(_("\n--- Menus ---"));

    show_menus_recursive(parent, modes, 0);
    return OK;
}
