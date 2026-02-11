update_label_date(property_t prop)
{
    prop_map_t *map_entry = settings_gui_get_map_entry(prop);
    GtkWidget *top = map_entry->fn_toplevel();
    GtkWidget *w;
	time_t t;

    if (!top)
        return FALSE;

    w = lookup_widget(top, map_entry->wid);
    if (w == NULL) {
		if (GUI_PROPERTY(gui_debug))
			g_warning("%s - widget not found: [%s]",
				 G_GNUC_PRETTY_FUNCTION, map_entry->wid);
        return FALSE;
    }

	gnet_prop_get_timestamp_val(prop, &t);
	if (t == 0) {
		gtk_label_set_text(GTK_LABEL(w), _("Never"));
	} else {
		static const gchar date_fmt[] = "%Y-%m-%d %H:%M:%S";
		gchar buf[128];
		size_t len;

		len = strftime(buf, sizeof buf, date_fmt, localtime(&t));
		buf[len] = '\0';
		gtk_label_set_text(GTK_LABEL(w), buf);
	}

    return FALSE;
}
