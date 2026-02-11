sylk_rtd_p_parse (SylkReader *state, char *str)
{
	char *next;
	int   font_size;
	GnmStyle *font = NULL;

	for (; *str != '\0' ; str = next) {
		next = sylk_next_token (str);
		switch (*str) {
		case 'P' :
			g_ptr_array_add (state->formats,
				go_format_new_from_XL (str+1));
			break;

		case 'F' :
			break;

		case 'E' :
			if (str[1] != '\0') {
				if (NULL == font) font = gnm_style_new ();
				gnm_style_set_font_name	(font, str+1);
			}
			break;

		case 'L' :
			break;

		case 'M' :
			if (sylk_parse_int (str+1, &font_size) &&
			    font_size > 0) {
				if (NULL == font) font = gnm_style_new ();
				gnm_style_set_font_size	(font, font_size / 20.0);
			}
			break;

		case 'S' :
			for (str++ ; *str && *str != ';' ; str++)
				switch (*str) {
				case 'I':
					if (NULL == font) font = gnm_style_new ();
					gnm_style_set_font_italic (font, TRUE);
					break;

				case 'B':
					if (NULL == font) font = gnm_style_new ();
					gnm_style_set_font_bold (font, TRUE);
					break;
				}
			break;
		default :
			sylk_read_warning (state, "unknown P option '%c'", *str);
		}
	}

	if (NULL != font)
		g_ptr_array_add (state->fonts, font);
	return TRUE;
}
