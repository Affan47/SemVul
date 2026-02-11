color_table_setup (GOComboColor *cc,
		   char const *no_color_label, GOColorGroup *color_group)
{
	g_return_if_fail (cc != NULL);


	cc->palette = (GOColorPalette *)go_color_palette_new (no_color_label,
		cc->default_color, color_group);
	g_signal_connect (cc->palette,
		"color_changed",
		G_CALLBACK (cb_palette_color_changed), cc);
	g_signal_connect (cc->palette,
		"display-custom-dialog",
		G_CALLBACK (cb_proxy_custom_dialog), cc);
	gtk_widget_show_all (GTK_WIDGET (cc->palette));
}
