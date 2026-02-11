scroll_get_tag(menu_type *menu, int pos)
{
	if (menu->selections)
		return menu->selections[pos - menu->top];

	return 0;
}
