gnome_desktop_item_set_boolean (GnomeDesktopItem *item,
				const char *attr,
				gboolean value)
{
	g_return_if_fail (item != NULL);
	g_return_if_fail (item->refcount > 0);
	g_return_if_fail (attr != NULL);

	set (item, attr, value ? "true" : "false");
}
