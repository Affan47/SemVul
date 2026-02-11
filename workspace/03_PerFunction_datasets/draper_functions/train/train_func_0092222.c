layout_config_widget(GtkWidget *group, GtkWidget *box, gint style, LayoutConfig *lc)
{
	GtkWidget *table;
	LayoutStyle ls;

	ls = layout_config_styles[style];

	if (group)
		{
		group = gtk_radio_button_new(gtk_radio_button_get_group(GTK_RADIO_BUTTON(group)));
		}
	else
		{
		group = gtk_radio_button_new(NULL);
		}
	g_object_set_data(G_OBJECT(group), "layout_config", lc);
	g_signal_connect(G_OBJECT(group), "clicked",
			 G_CALLBACK(layout_config_widget_click_cb), GINT_TO_POINTER(style));
	gtk_box_pack_start(GTK_BOX(box), group, FALSE, FALSE, 0);

	table = gtk_table_new(2, 2, TRUE);

	layout_config_table_button(table, ls.a, "1");
	layout_config_table_button(table, ls.b, "2");
	layout_config_table_button(table, ls.c, "3");

	gtk_widget_set_size_request(table, LAYOUT_STYLE_SIZE, LAYOUT_STYLE_SIZE);
	gtk_container_add(GTK_CONTAINER(group), table);
	gtk_widget_show(table);

	gtk_widget_show(group);

	return group;
}
