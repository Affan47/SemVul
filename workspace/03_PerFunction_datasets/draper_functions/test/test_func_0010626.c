build_get_menu_items(gint filetype_idx)
{
	BuildMenuItems *items;

	items = &menu_items;
	if (items->menu == NULL)
		create_build_menu(items);
	return items;
}
