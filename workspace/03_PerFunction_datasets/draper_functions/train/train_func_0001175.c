add_color_selector(GtkWidget *page, gchar *name, gchar *gconf_path, MultiloadApplet *ma)
{
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *color_picker;
	GdkColor color;
	gchar *color_string;

	color_string = panel_applet_gconf_get_string(ma->applet, gconf_path, NULL);
	if (!color_string)
		color_string = g_strdup ("#000000");
	color.red   = (g_ascii_xdigit_value(color_string[1]) * 16
                       + g_ascii_xdigit_value(color_string[2])) * 256;
	color.green = (g_ascii_xdigit_value(color_string[3]) * 16
                       + g_ascii_xdigit_value(color_string[4])) * 256;
	color.blue  = (g_ascii_xdigit_value(color_string[5]) * 16
                       + g_ascii_xdigit_value(color_string[6])) * 256;
	g_free (color_string);

	vbox = gtk_vbox_new (FALSE, 6);
	label = gtk_label_new_with_mnemonic(name);
	color_picker = gtk_color_button_new();
	gtk_label_set_mnemonic_widget (GTK_LABEL (label), color_picker);

	gtk_box_pack_start(GTK_BOX(vbox), color_picker, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(page), vbox, FALSE, FALSE, 0);

	g_object_set_data (G_OBJECT (color_picker), "MultiloadApplet", ma);

	gtk_color_button_set_color(GTK_COLOR_BUTTON(color_picker), &color);

	g_signal_connect(G_OBJECT(color_picker), "color_set", G_CALLBACK(color_picker_set_cb), gconf_path);

	if ( ! key_writable (ma->applet, gconf_path))
		hard_set_sensitive (vbox, FALSE);

	return;
}
