gui_is_menu_shortcut(key)
    int		key;
{
    vimmenu_T	*menu;

    if (key < 256)
	key = TOLOWER_LOC(key);
    for (menu = root_menu; menu != NULL; menu = menu->next)
	if (menu->mnemonic == key
		|| (menu->mnemonic < 256 && TOLOWER_LOC(menu->mnemonic) == key))
	    return TRUE;
    return FALSE;
}
