should_show_volume_usage (NemoPropertiesWindow *window)
{
	NemoFile 		*file;
	gboolean 		success = FALSE;

	if (is_multi_file_window (window)) {
		return FALSE;
	}

	file = get_original_file (window);

	if (file == NULL) {
		return FALSE;
	}

	if (nemo_file_can_unmount (file)) {
		return TRUE;
	}

#ifdef TODO_GIO

#endif
	return success;
}
