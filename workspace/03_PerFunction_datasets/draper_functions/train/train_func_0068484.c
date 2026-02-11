gnm_graph_window_init (GnmGraphWindow *window)
{
	GtkToolItem *item;
	unsigned int i;


	static char const * chart_sizes[] = {
		N_("Fit"),
		N_("Fit Width"),
		N_("Fit Height"),
		"SEPARATOR",
		N_("100%"),
		N_("125%"),
		N_("150%"),
		N_("200%"),
		N_("300%"),
		N_("500%")
	};

	window->vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show (GTK_WIDGET (window->vbox));
	gtk_container_add (GTK_CONTAINER (window), window->vbox);

	window->toolbar = gtk_toolbar_new ();
	gtk_widget_show (GTK_WIDGET (window->toolbar));
	gtk_box_pack_start (GTK_BOX (window->vbox), window->toolbar, FALSE, FALSE, 0);

	window->scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (GTK_WIDGET (window->scrolled_window));
	gtk_container_add (GTK_CONTAINER (window->vbox), window->scrolled_window);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (window->scrolled_window),
					GTK_POLICY_NEVER, GTK_POLICY_NEVER);

	item = gtk_tool_item_new ();
	gtk_widget_show (GTK_WIDGET (item));
	gtk_toolbar_insert (GTK_TOOLBAR (window->toolbar), item, -1);

	window->size_combo = gtk_combo_box_text_new ();
	for (i = 0; i < G_N_ELEMENTS (chart_sizes); i++)
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (window->size_combo), _(chart_sizes[i]));
	gtk_widget_set_sensitive (window->size_combo, FALSE);
	gtk_widget_show (window->size_combo);
	gtk_combo_box_set_active (GTK_COMBO_BOX (window->size_combo), CHART_SIZE_FIT);
	gtk_combo_box_set_row_separator_func (GTK_COMBO_BOX (window->size_combo),
					      size_combo_is_row_separator, NULL, NULL);
	gtk_container_add (GTK_CONTAINER (item), window->size_combo);
	g_signal_connect_swapped (window->size_combo, "changed",
				  G_CALLBACK (update_graph_sizing_mode), window);

	item = gtk_tool_button_new_from_stock (GTK_STOCK_FULLSCREEN);
	gtk_widget_show (GTK_WIDGET (item));

	gtk_toolbar_insert (GTK_TOOLBAR (window->toolbar), item, -1);
	g_signal_connect (item, "clicked",
			  G_CALLBACK (fullscreen_button_clicked), window);

	gtk_window_set_title (GTK_WINDOW (window), "Chart Viewer");
}
