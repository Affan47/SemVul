fullscreen_prefs_selection_new(const gchar *text, gint *screen_value, gboolean *above_value)
{
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *combo;
	GtkListStore *store;
	GtkCellRenderer *renderer;
	GtkWidget *button = NULL;
	GList *list;
	GList *work;
	gint current = 0;
	gint n;

	if (!screen_value) return NULL;

	vbox = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	hbox = pref_box_new(vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	if (text) pref_label_new(hbox, text);

	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
	combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer,
				       "text", FS_MENU_COLUMN_NAME, NULL);

	if (above_value)
		{
		button = pref_checkbox_new_int(vbox, _("Stay above other windows"),
					       *above_value, above_value);
		gtk_widget_set_sensitive(button, *screen_value != -1);

		g_object_set_data(G_OBJECT(combo), BUTTON_ABOVE_KEY, button);
		}

	fullscreen_prefs_selection_add(store, _("Determined by Window Manager"), -1);
	fullscreen_prefs_selection_add(store, _("Active screen"), 0);
	if (*screen_value == 0) current = 1;
	fullscreen_prefs_selection_add(store, _("Active monitor"), 1);
	if (*screen_value == 1) current = 2;

	n = 3;
	list = fullscreen_prefs_list();
	work = list;
	while (work)
		{
		ScreenData *sd = work->data;

		fullscreen_prefs_selection_add(store, sd->description, sd->number);
		if (*screen_value == sd->number) current = n;

		work = work->next;
		n++;
		}
	fullscreen_prefs_list_free(list);

	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), current);

	gtk_box_pack_start(GTK_BOX(hbox), combo, FALSE, FALSE, 0);
	gtk_widget_show(combo);

	g_signal_connect(G_OBJECT(combo), "changed",
			 G_CALLBACK(fullscreen_prefs_selection_cb), screen_value);

	return vbox;
}
