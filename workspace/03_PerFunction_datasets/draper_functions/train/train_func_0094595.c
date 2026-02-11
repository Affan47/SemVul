reset_parse(char *text)
{
	if (text != NULL) {
		Mp = text;
	} else {
		Mp = Mission_text;
	}

	Warning_count = 0;
	Error_count = 0;

	strcpy_s(parse_error_text, "");

	strcpy_s(Current_filename, Current_filename_sub);
}
