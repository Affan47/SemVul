stickynotes_applet_init_icons(void)
{
	GtkIconFactory *icon_factory = gtk_icon_factory_new();

	gint i;
	for (i = 0; i < G_N_ELEMENTS(stickynotes_icons); i++) {
		StickyNotesStockIcon icon = stickynotes_icons[i];
		GtkIconSource *icon_source = gtk_icon_source_new();
		GtkIconSet *icon_set = gtk_icon_set_new();

		gtk_icon_source_set_filename(icon_source, icon.filename);
		gtk_icon_set_add_source(icon_set, icon_source);
		gtk_icon_factory_add(icon_factory, icon.stock_id, icon_set);

		gtk_icon_source_free(icon_source);
		gtk_icon_set_unref(icon_set);
	}

	gtk_icon_factory_add_default(icon_factory);

	g_object_unref(G_OBJECT(icon_factory));
}
