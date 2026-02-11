nemo_icon_container_search_init (GtkWidget   *entry,
				     NemoIconContainer *container)
{
	gint ret;
	gint len;
	const gchar *text;

	g_assert (GTK_IS_ENTRY (entry));
	g_assert (NEMO_IS_ICON_CONTAINER (container));

	text = gtk_entry_get_text (GTK_ENTRY (entry));
	len = strlen (text);


	unselect_all (container);
	reset_search_entry_timeout (container);

	if (len < 1) {
		return;
	}

	ret = nemo_icon_container_search_iter (container, text, 1);

	if (ret) {
		container->details->selected_iter = 1;
	}
}
