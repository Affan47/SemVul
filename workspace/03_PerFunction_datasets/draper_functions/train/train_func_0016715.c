draw_text(struct view *view, enum line_type type, const char *string)
{
	char text[SIZEOF_STR];

	do {
		size_t pos = string_expand(text, sizeof(text), string, opt_tab_size);

		if (draw_chars(view, type, text, VIEW_MAX_LEN(view), TRUE))
			return TRUE;
		string += pos;
	} while (*string);

	return VIEW_MAX_LEN(view) <= 0;
}
