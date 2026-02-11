should_show_open_with (NemoPropertiesWindow *window)
{
	NemoFile *file;


	if (is_multi_file_window (window)) {
		if (!file_list_attributes_identical (window->details->original_files,
						     "mime_type")) {
			return FALSE;
		} else {

			GList *l;

			for (l = window->details->original_files; l; l = l->next) {
				file = NEMO_FILE (l->data);
				if (nemo_file_is_directory (file) ||
				    is_a_special_file (file)) {
					return FALSE;
				}
			}
		}
	} else {
		file = get_original_file (window);
		if (nemo_file_is_directory (file) ||
		    is_a_special_file (file)) {
			return FALSE;
		}
	}
	return TRUE;
}
