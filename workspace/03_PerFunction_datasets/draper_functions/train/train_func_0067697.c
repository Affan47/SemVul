gnome_desktop_item_set_strings (GnomeDesktopItem *item,
				const char *attr,
				char **strings)
{
	char *str, *str2;

	g_return_if_fail (item != NULL);
	g_return_if_fail (item->refcount > 0);
	g_return_if_fail (attr != NULL);

	str = g_strjoinv (";", strings);
	str2 = g_strconcat (str, ";", NULL);

	set (item, attr, str2);
	g_free (str);
	g_free (str2);
}
