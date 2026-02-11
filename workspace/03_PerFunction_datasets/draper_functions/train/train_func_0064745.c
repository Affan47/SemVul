menuitem_create_checkbox(char *id, MenuEventFunc(*event_func),
	char *text, Client *client, bool allow_gray, bool value)
{
	MenuItem *new_item;

	debug(RPT_DEBUG, "%s(id=[%s], event_func=%p, text=\"%s\", allow_gray=%d, value=%d)",
			__FUNCTION__, id, event_func, text, allow_gray, value);

	new_item = menuitem_create(MENUITEM_CHECKBOX, id, event_func, text, client);
	if (new_item != NULL) {
		new_item->data.checkbox.allow_gray = allow_gray;
		new_item->data.checkbox.value = value;
	}

	return new_item;
}
