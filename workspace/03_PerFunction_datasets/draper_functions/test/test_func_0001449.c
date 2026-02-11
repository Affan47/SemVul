get_menu_name(xp, idx)
    expand_T	*xp;
    int		idx;
{
    static vimmenu_T	*menu = NULL;
    char_u		*str;

    if (idx == 0)
	menu = expand_menu;


    while (menu != NULL && (menu_is_hidden(menu->dname)
	    || menu_is_separator(menu->dname)
	    || menu_is_tearoff(menu->dname)
	    || menu->children == NULL))
	menu = menu->next;

    if (menu == NULL)
	return NULL;

    if (menu->modes & expand_modes)
	str = menu->dname;
    else
	str = (char_u *)"";


    menu = menu->next;

    return str;
}
