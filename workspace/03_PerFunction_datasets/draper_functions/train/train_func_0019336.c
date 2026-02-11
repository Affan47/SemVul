custom_attr_default_list(void)
{

	GList *list;
	gint i;
	i = 0;

	list = NULL;
	while (default_addressbook_attributes_table[i]) {
		list = g_list_prepend(
			list, g_strdup(gettext(default_addressbook_attributes_table[i])));
		i++;
	}
	list = g_list_reverse(list);
	return list;
}
