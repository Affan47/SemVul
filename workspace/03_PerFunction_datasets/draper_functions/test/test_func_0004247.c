verify_click_pos(GeanyDocument *doc)
{
	if (insert_callback_from_menu)
	{
		editor_info.click_pos = sci_get_current_position(doc->editor->sci);
		insert_callback_from_menu = FALSE;
	}
}
