cui_theme_get_tethering_icone_and_info(GdkPixbuf **image,
							const char **info)
{
	if (image != NULL)
		*image = gtk_icon_theme_load_icon(cui_theme,
					"tethering", 24, 0, NULL);
	if (info != NULL)
		*info = _("Tethering");
}
