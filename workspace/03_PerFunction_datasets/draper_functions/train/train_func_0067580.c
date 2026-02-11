print_tty_data(const char *val)
{
	int need_comma, in_printable = 0;
	unsigned char *data, *data_pos, *data_end;

	if (!is_hex_string(val)) {
		printf("%s", val);
		return;
	}

	if ((data = unescape((char *)val)) == NULL) {
		printf("conversion error(%s)", val);
		return;
	}

	data_end = data + strlen(val) / 2;
	data_pos = data;
	need_comma = 0;
	while (data_pos < data_end) {

		const char *desc;

		desc = tty_find_named_key(&data_pos, data_end - data_pos);
		if (desc != NULL) {
			if (in_printable != 0) {
				putchar('"');
				in_printable = 0;
			}
			if (need_comma != 0)
				putchar(',');
			printf("<%s>", desc);
		} else {
			if (in_printable == 0) {
				if (need_comma != 0)
					putchar(',');
				putchar('"');
				in_printable = 1;
			}
			tty_printable_char(*data_pos);
			data_pos++;
		}
		need_comma = 1;
	}
	if (in_printable != 0)
		putchar('"');
	free(data);
}
