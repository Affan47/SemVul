menubar_get_attribute(state_t *s, int menu_nr, int item_nr, int attribute)
{
	menubar_t *menubar = s->menubar;
	menu_item_t *item;

	if ((menu_nr < 0) || (item_nr < 0))
		return make_reg(0, -1);

	if ((menu_nr >= menubar->menus_nr) || (item_nr >= menubar->menus[menu_nr].items_nr))
		return make_reg(0, -1);

	item = menubar->menus[menu_nr].items + item_nr;

	switch (attribute) {
	case MENU_ATTRIBUTE_SAID:
		return item->said_pos;

	case MENU_ATTRIBUTE_TEXT:
		return item->text_pos;

	case MENU_ATTRIBUTE_KEY:
		return make_reg(0, item->key);

	case MENU_ATTRIBUTE_ENABLED:
		return make_reg(0, item->enabled);

	case MENU_ATTRIBUTE_TAG:
		return make_reg(0, item->tag);

	default:
		sciprintf("Attempt to read invalid attribute from menu %d, item %d: 0x%04x\n",
			  menu_nr, item_nr, attribute);
		return make_reg(0, -1);
	}
}
