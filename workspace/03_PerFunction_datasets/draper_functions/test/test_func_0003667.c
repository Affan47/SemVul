rig_utils_index_to_mode (gint index)
{
	guint mode;


	if ((index >= 0) && (index <= 15)) {
		mode = 1 << index;
	}
	else {
		mode = 1;
	}

	return mode;
}
