getText(int *len, const char *format)
{
	GdkAtom target = GDK_NONE;
	gint n_tg;
	GdkAtom *targets;
	char *fmt;
	int i;
	GtkSelectionData *data;
	char *text;

	*len = 0;

	if (!gtk_clipboard_wait_for_targets(_clipboard, &targets, &n_tg) || n_tg <= 0)
		return NULL;

	for (i = 0; i < n_tg; i++)
	{
		target = targets[i];
		fmt = convert_format(gt_free_later(gdk_atom_name(target)));
		if (!islower(fmt[0]))
			continue;
		if (!format && !strncasecmp(fmt, "text/", 5))
			break;
		if (format && !strcasecmp(fmt, format))
			break;
	}

	if (i >= n_tg)
		return NULL;

	if (!gtk_clipboard_wait_is_target_available(_clipboard, target))
		return NULL;

	data = gtk_clipboard_wait_for_contents(_clipboard, target);

	*len = data->length;
	text = (char *)g_malloc(*len);
	memcpy(text, data->data, *len);

	gtk_selection_data_free(data);

	return gt_free_later(text);
}
