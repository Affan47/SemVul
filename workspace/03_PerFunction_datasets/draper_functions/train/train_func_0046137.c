interpolate_titleformat_name(FvwmWindow *fw, window_style *style,
		Bool is_icon)
{
	char stringbuf[MAX_VISIBLE_NAME_LEN] = "";


	const char *format;
	int count;


	char win_name_len[MAX_WINDOW_NAME_NUMBER_DIGITS];
	char w_id[12];

	if (is_icon)
	{
		format = (style->flags.has_icon_title_format_string) ?
			SGET_ICON_TITLE_FORMAT_STRING(*style) :
			DEFAULT_TITLE_FORMAT;
	} else {
		format = (style->flags.has_title_format_string) ?
			SGET_TITLE_FORMAT_STRING(*style) :
			DEFAULT_TITLE_FORMAT;
	}

	while (*format)
	{
		int pos;
		for (pos = 0; format[pos] && format[pos] != '%'; pos++);

		strncat(stringbuf, format, pos);
		format += pos;

		if (*format != '%')
			continue;

		format++;
		switch (*format)
		{
			case 'n':
				if (strlen(stringbuf) +
					strlen(fw->name.name) >
					MAX_VISIBLE_NAME_LEN)
				{
					fvwm_msg(WARN,
					"interpolate_titleformat_name",
					"Visible name is too long based on "
					"TitleFormat.  Not expanding further.");

					break;
				}

				strcat(stringbuf, fw->name.name);
				break;
			case 'c':
				if (strlen(stringbuf) +
					strlen(fw->class.res_class) >
					MAX_VISIBLE_NAME_LEN)
				{
					fvwm_msg(WARN,
					"interpolate_titleformat_name",
					"Visible name is too long based on "
					"TitleFormat.  Not expanding further.");

					break;
				}
				strcat(stringbuf, fw->class.res_class);
				break;
			case 'i':
				if (strlen(stringbuf) +
					strlen(fw->icon_name.name) >
					MAX_VISIBLE_NAME_LEN)
				{
					fvwm_msg(WARN,
					"interpolate_titleformat_name",
					"Visible name is too long based on "
					"TitleFormat.  Not expanding further.");

					break;
				}

				strcat(stringbuf, fw->icon_name.name);
				break;
			case 'r':
				if (strlen(stringbuf) +
					strlen(fw->class.res_name) >
					MAX_VISIBLE_NAME_LEN)
				{
					fvwm_msg(WARN,
					"interpolate_titleformat_name",
					"Visible name is too long based on "
					"TitleFormat.  Not expanding further.");

					break;
				}
				strcat(stringbuf, fw->class.res_name);
				break;
			case 't':
				setup_name_count(fw, is_icon);
				count = is_icon ? fw->icon_name_count :
					fw->name_count;

				if (count > (MAX_WINDOW_NAME_NUMBER - 1))
					count = MAX_WINDOW_NAME_NUMBER - 1;

				sprintf(win_name_len, "%d", ++count);
				strcat(stringbuf, win_name_len);
				break;
			case 'I':
				sprintf(w_id, "0x%x", (int)FW_W(fw));
				strcat(stringbuf, w_id);
				break;
			case '%':
				strcat(stringbuf, "%");
				break;
			default:
				break;
		}
		if (*format)
			format++;
	}

	return strdup(stringbuf);
}
