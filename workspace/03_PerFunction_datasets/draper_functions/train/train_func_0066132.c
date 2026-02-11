bar_pane_exif_update_entry(PaneExifData *ped, GtkWidget *entry, gboolean update_title)
{
	gchar *text;
	ExifEntry *ee = g_object_get_data(G_OBJECT(entry), "entry_data");

	if (!ee) return;
	text = metadata_read_string(ped->fd, ee->key, ee->editable ? METADATA_PLAIN : METADATA_FORMATTED);

	if (!ped->show_all && ee->if_set && !ee->editable && (!text || !*text))
		{
		gtk_label_set_text(GTK_LABEL(ee->value_widget), NULL);
		gtk_widget_hide(entry);
		}
	else
		{
		if (ee->editable)
			{
			g_signal_handlers_block_by_func(ee->value_widget, bar_pane_exif_entry_changed, ee);
			gtk_entry_set_text(GTK_ENTRY(ee->value_widget), text ? text : "");
			g_signal_handlers_unblock_by_func(ee->value_widget, bar_pane_exif_entry_changed, ee);
			gtk_widget_set_tooltip_text(ee->box, NULL);
			}
		else
			{
			gtk_label_set_text(GTK_LABEL(ee->value_widget), text);
			gtk_widget_set_tooltip_text(ee->box, text);
			}
		gtk_widget_show(entry);
		ped->all_hidden = FALSE;
		}

	g_free(text);

	if (update_title) bar_pane_exif_entry_update_title(ee);
}
