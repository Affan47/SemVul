_e2_combobox_changed_cb (GtkWidget *combo, gpointer data)
{

	if (g_object_get_data (G_OBJECT (combo), "e2_changed_blocked") != NULL)
	{

		return;
	}

	if ((GTK_WIDGET_VISIBLE (combo)) &&
		(gtk_combo_box_get_active (GTK_COMBO_BOX (combo)) != -1))
	{
		gboolean focus = GPOINTER_TO_INT (data);
		GtkWidget *entry = GTK_BIN (combo)->child;
		if (focus)
		{
			gtk_widget_grab_focus (entry);
			gtk_editable_set_position (GTK_EDITABLE (entry), -1);
		}
		else
			g_signal_emit_by_name (G_OBJECT (entry), "activate");
	}
}
