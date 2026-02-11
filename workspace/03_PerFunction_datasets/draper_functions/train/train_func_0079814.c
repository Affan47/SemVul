colorlabel_create_color_menu(void)
{
	GtkWidget *label;
	GtkWidget *item;
	GtkWidget *menu;
	gint i;

	colorlabel_recreate_all();


	menu = gtk_menu_new();
	g_object_set_data(G_OBJECT(menu), "label_color_menu", menu);

	item = gtk_menu_item_new_with_label(_("None"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	g_object_set_data(G_OBJECT(item), "color", GUINT_TO_POINTER(0));
	gtk_widget_show(item);

	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	gtk_widget_show(item);


	for (i = 0; i < LABEL_COLORS_ELEMS; i++) {
		GtkWidget *hbox;
		GtkWidget *vbox;
		GtkWidget *widget;

		item  = gtk_menu_item_new();
		g_object_set_data(G_OBJECT(item), "color",
				  GUINT_TO_POINTER(i + 1));

		label = gtk_label_new(label_colors[0][i].label);

		gtk_widget_show(label);
		hbox = gtk_hbox_new(FALSE, 0);
		gtk_widget_show(hbox);
		gtk_container_add(GTK_CONTAINER(item), hbox);

		vbox = gtk_vbox_new(TRUE, 0);
		gtk_widget_show(vbox);
		gtk_container_set_border_width(GTK_CONTAINER(vbox), 1);

		widget = colorlabel_create_color_widget(label_colors[0][i].color);
		gtk_widget_show(widget);
		gtk_box_pack_start(GTK_BOX(vbox), widget, FALSE, FALSE, 0);

		gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 4);

		gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
		gtk_widget_show(item);
	}

	g_signal_connect(G_OBJECT(menu), "selection-done",
			G_CALLBACK(refresh_menu), menu);
	gtk_widget_show(menu);

	return menu;
}
