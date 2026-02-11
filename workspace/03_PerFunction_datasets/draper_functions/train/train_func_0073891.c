gusb_cmd_add (GPtrArray *array, const gchar *name, const gchar *description, GUsbCmdPrivateCb callback)
{
	gchar **names;
	guint i;
	GUsbCmdItem *item;


	names = g_strsplit (name, ",", -1);
	for (i=0; names[i] != NULL; i++) {
		item = g_slice_new0 (GUsbCmdItem);
		item->name = g_strdup (names[i]);
		if (i == 0) {
			item->description = g_strdup (description);
		} else {

			item->description = g_strdup_printf ("Alias to %s",
							     names[0]);
		}
		item->callback = callback;
		g_ptr_array_add (array, item);
	}
	g_strfreev (names);
}
