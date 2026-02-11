ok_colorsel(GtkWidget *widget,gpointer *data){

	GdkColor color;
	gchar *color_name;
	gchar buff[128];
	gchar *title;

	LOG(LOG_DEBUG, "IN : ok_colorsel()");

	gtk_grab_remove(colorsel_dlg);

	gtk_color_selection_get_current_color(GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(colorsel_dlg)->colorsel), &color);
	color_name = gtk_color_selection_palette_to_string(&color, 1);

	if(color_no == 0){
		sprintf(fg_color, "%s", color_name);
	} else {
		sprintf(bg_color, "%s", color_name);
	}

	title = (gchar *)gtk_entry_get_text(GTK_ENTRY(entry_title));
	if(strlen(fg_color) == 0){
		if(strlen(bg_color) == 0)
			sprintf(buff, _("Sample"));
		else
			sprintf(buff, "<span background=\"%s\">%s</span>", bg_color, _("Sample"));
	} else {
		if(strlen(bg_color) == 0)
			sprintf(buff, "<span foreground=\"%s\">%s</span>", fg_color, _("Sample"));
			else
				sprintf(buff, "<span foreground=\"%s\" background=\"%s\">%s</span>", fg_color, bg_color, _("Sample"));
	}
	gtk_label_set_text(GTK_LABEL(label_color), buff);
	gtk_label_set_use_markup (GTK_LABEL (label_color), TRUE);

	gtk_widget_destroy(colorsel_dlg);

	LOG(LOG_DEBUG, "OUT : ok_colorsel()");
}
