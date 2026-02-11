nemo_notebook_sync_loading (NemoNotebook *notebook,
				NemoWindowSlot *slot)
{
	GtkWidget *tab_label, *spinner, *icon;
	gboolean active;

	g_return_if_fail (NEMO_IS_NOTEBOOK (notebook));
	g_return_if_fail (NEMO_IS_WINDOW_SLOT (slot));

	tab_label = gtk_notebook_get_tab_label (GTK_NOTEBOOK (notebook),
						GTK_WIDGET (slot));
	g_return_if_fail (GTK_IS_WIDGET (tab_label));

	spinner = GTK_WIDGET (g_object_get_data (G_OBJECT (tab_label), "spinner"));
	icon = GTK_WIDGET (g_object_get_data (G_OBJECT (tab_label), "icon"));
	g_return_if_fail (spinner != NULL && icon != NULL);

	active = FALSE;
	g_object_get (spinner, "active", &active, NULL);
	if (active == slot->allow_stop)	{
		return;
	}

	if (slot->allow_stop) {
		gtk_widget_hide (icon);
		gtk_widget_show (spinner);
		gtk_spinner_start (GTK_SPINNER (spinner));
	} else {
		gtk_spinner_stop (GTK_SPINNER (spinner));
		gtk_widget_hide (spinner);
		gtk_widget_show (icon);
	}
}
