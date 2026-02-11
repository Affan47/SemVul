theme_format_append_next(THEME_REC *theme, GString *str,
				     const char **format,
				     char default_fg, char default_bg,
				     char *last_fg, char *last_bg,
				     int flags)
{
	int index;
	unsigned char chr;

	chr = **format;
	if ((chr == '$' || chr == '%') &&
	    (*format)[1] == '\0') {

		g_string_append_c(str, chr);
		(*format)++;
                return;
	}

	if (chr == '$') {


		theme_format_append_variable(str, format);
		return;
	}

	if (**format == '%') {

		(*format)++;
		if (**format != '{' && **format != '}') {
                        chr = **format;
			if (**format == 'n') {

				g_string_append(str, "%n");

				if (default_bg != 'n') {
					g_string_append_c(str, '%');
					g_string_append_c(str, default_bg);
				}
				if (default_fg != 'n') {
					g_string_append_c(str, '%');
					g_string_append_c(str, default_fg);
				}

				*last_fg = default_fg;
				*last_bg = default_bg;
			} else {
				if (IS_FGCOLOR_FORMAT(chr))
					*last_fg = chr;
				if (IS_BGCOLOR_FORMAT(chr))
					*last_bg = chr;
				g_string_append_c(str, '%');
				g_string_append_c(str, chr);
			}
			(*format)++;
			return;
		}


		g_string_append_c(str, '%');
		chr = **format;
	}

	index = (flags & EXPAND_FLAG_IGNORE_REPLACES) ? -1 :
		theme->replace_keys[(int) (unsigned char) chr];
	if (index == -1)
		g_string_append_c(str, chr);
	else {
		char *value;

		value = theme_replace_expand(theme, index,
					     default_fg, default_bg,
					     last_fg, last_bg, chr, flags);
		g_string_append(str, value);
		g_free(value);
	}

        (*format)++;
}
