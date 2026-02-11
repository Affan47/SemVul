nemo_file_should_show (NemoFile *file,
			   gboolean show_hidden,
			   gboolean show_foreign)
{

	if (nemo_file_is_in_trash (file)) {
		return TRUE;
	} else {
		return (show_hidden || (!nemo_file_is_hidden_file (file) && !is_file_hidden (file))) &&
			(show_foreign || !(nemo_file_is_in_desktop (file) && nemo_file_is_foreign_link (file)));
	}
}
