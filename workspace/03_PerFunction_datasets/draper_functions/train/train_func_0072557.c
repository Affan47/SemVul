gnome_desktop_item_save (GnomeDesktopItem *item,
			 const char *under,
			 gboolean force,
			 GError **error)
{
	const char *uri;

	if (under == NULL &&
	    ! force &&
	    ! item->modified)
		return TRUE;

	if (under == NULL)
		uri = item->location;
	else
		uri = under;

	if (uri == NULL) {
		g_set_error (error,
			     GNOME_DESKTOP_ITEM_ERROR,
			     GNOME_DESKTOP_ITEM_ERROR_NO_FILENAME,
			     _("No filename to save to"));
		return FALSE;
	}

	if ( ! ditem_save (item, uri, error))
		return FALSE;

	item->modified = FALSE;
	item->mtime = time (NULL);

	return TRUE;
}
