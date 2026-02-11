on_addbutton_clicked(GtkButton *button, gpointer user_data)
{
	if (button){};

	GladeXML *gxml = glade_xml_new (GLADE_FILE_RULE_ADD, NULL, NULL);

	GtkWidget *window = glade_xml_get_widget (gxml, "dialog1");

	gtk_widget_show(window);

	xyz_t *ud = malloc(sizeof(xyz_t));
	ud->x = gxml;
	ud->y = ((xyz_t *) user_data)->y;

	GtkWidget *widget= glade_xml_get_widget (gxml, "button1");
	g_signal_connect ((gpointer) widget, "clicked", G_CALLBACK (new_rule_to_treeview), ud);
	widget = glade_xml_get_widget (gxml, "button2");
	g_signal_connect ((gpointer) widget, "clicked", G_CALLBACK (on_cancelbutton_clicked), ud);

}
