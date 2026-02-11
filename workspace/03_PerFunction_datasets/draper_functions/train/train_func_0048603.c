lacks_top_left (NemoFile *file)
{
	return file->details->file_info_is_up_to_date &&
		!file->details->top_left_text_is_up_to_date
		&& nemo_file_should_get_top_left_text (file);
}
