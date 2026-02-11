gst_sbc_get_mode_from_list(const GValue *list, gint channels)
{
	unsigned int i;
	const GValue *value;
	const gchar *aux;
	gboolean joint, stereo, dual, mono;
	guint size = gst_value_list_get_size(list);

	joint = stereo = dual = mono = FALSE;

	for (i = 0; i < size; i++) {
		value = gst_value_list_get_value(list, i);
		aux = g_value_get_string(value);
		if (strcmp("joint", aux) == 0)
			joint = TRUE;
		else if (strcmp("stereo", aux) == 0)
			stereo = TRUE;
		else if (strcmp("dual", aux) == 0)
			dual = TRUE;
		else if (strcmp("mono", aux) == 0)
			mono = TRUE;
	}

	if (channels == 1 && mono)
		return "mono";
	else if (channels == 2) {
		if (joint)
			return "joint";
		else if (stereo)
			return "stereo";
		else if (dual)
			return "dual";
	}

	return NULL;
}
