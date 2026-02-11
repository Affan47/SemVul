is_valid_row(menu_type *menu, int cursor)
{
	int oid = cursor;

	if (cursor < 0 || cursor >= menu->filter_count)
		return FALSE;

	if (menu->filter_list)
		oid = menu->filter_list[cursor];

	if (!menu->row_funcs->valid_row)
		return TRUE;

	return menu->row_funcs->valid_row(menu, oid);
}
