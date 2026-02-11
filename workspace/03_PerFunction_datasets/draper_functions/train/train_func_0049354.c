menu_get_subitem(Menu *menu, int index)
{
	MenuItem *item;
	int i = 0;

	debug(RPT_DEBUG, "%s(menu=[%s], index=%d)", __FUNCTION__,
			((menu != NULL) ? menu->id : "(null)"), index);
	for (item = LL_GetFirst(menu->data.menu.contents);
	     item != NULL;
	     item = LL_GetNext(menu->data.menu.contents)) {

		if (! item->is_hidden) {
			if (i == index)
				return item;
			++i;
		}
	}
	return NULL;
}
