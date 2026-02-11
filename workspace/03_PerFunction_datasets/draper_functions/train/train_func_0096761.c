on_gm_worlds_view_world_option_changed(GmOptions *options,
		gchar const *key, GmWorldsView *view) {
	GtkTreeIter iter;
	GtkListStore *store = GTK_LIST_STORE(view->priv->model);
	gchar *text;
	gchar const *logo;
	GdkPixbuf *pix_logo;
	GmWorld *world;

	if (!gm_worlds_view_find_by_options(view, options, &iter, &world)) {
		return;
	}

	if (strcmp(key, "name") == 0 ||
			strcmp(key, "player_name") == 0 ||
			strcmp(key, "host") == 0) {
		text = gm_worlds_view_world_text(view, world);
		gtk_list_store_set(store, &iter, GM_WORLDS_VIEW_NAME_COLUMN, text, -1);
		g_free(text);
	} else if (strcmp(key, "logo")) {
		logo = gm_options_get(options, "logo");

		if (logo) {
			pix_logo = gm_pixbuf_get_at_size(logo, 32, 32);
		} else {
			pix_logo = gm_pixbuf_get_at_size("world.svg", 32, 32);
		}

		gtk_list_store_set(store, &iter, GM_WORLDS_VIEW_LOGO_COLUMN,
				pix_logo, -1);
	}
}
