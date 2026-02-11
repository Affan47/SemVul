seahorse_util_filename_for_objects (GList *objects)
{
	SeahorseObject *object;
	const gchar *name;
	gchar *filename;

	g_return_val_if_fail (g_list_length (objects) > 0, NULL);

	if (g_list_length (objects) == 1) {
		g_return_val_if_fail (SEAHORSE_IS_OBJECT (objects->data), NULL);
		object = SEAHORSE_OBJECT (objects->data);
		name = seahorse_object_get_nickname (object);
		if (name == NULL)
			name = _("Key Data");
	} else {
		name = _("Multiple Keys");
	}

	filename = g_strconcat (name, SEAHORSE_EXT_ASC, NULL);
	g_strstrip (filename);
	g_strdelimit (filename, bad_filename_chars, '_');
	return filename;
}
