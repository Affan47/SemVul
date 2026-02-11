cut()
{
	if (selecting)
	{
		int start = get_selection_start();
		int end = get_selection_length();

		input_undo.removeString( text.substr( start, end ), start );

		text.erase(start, end);
		cursor_position = start;

		selecting = false;
		selection_start = selection_end = -1;

		if (cursor_position > (int)text.length())
			cursor_position = (int)text.length();

		sig_changed(text);
	}
}
