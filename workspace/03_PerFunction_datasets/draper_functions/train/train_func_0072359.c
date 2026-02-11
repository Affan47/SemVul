gnm_soc_get_target_list (SheetObject const *so)
{
	GtkTargetList *tl = gtk_target_list_new (NULL, 0);
	char *mime_str = go_image_format_to_mime ("svg");
	GSList *mimes, *ptr;

	mimes = go_strsplit_to_slist (mime_str, ',');
	for (ptr = mimes; ptr != NULL; ptr = ptr->next) {
		const char *mime = ptr->data;

		if (mime != NULL && *mime != '\0')
			gtk_target_list_add (tl, gdk_atom_intern (mime, FALSE),
					     0, 0);
	}
	g_free (mime_str);
	g_slist_free_full (mimes, g_free);

	gtk_target_list_add_image_targets (tl, 0, TRUE);

	return tl;
}
