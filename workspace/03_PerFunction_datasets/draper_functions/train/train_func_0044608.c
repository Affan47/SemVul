menu_is_menubar(name)
    char_u	*name;
{
    return (!menu_is_popup(name)
	    && !menu_is_toolbar(name)
	    && *name != MNU_HIDDEN_CHAR);
}
