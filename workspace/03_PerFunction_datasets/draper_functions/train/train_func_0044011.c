load_printf_template(void)
{
	FILE* fd = fopen(opt.template_file, "rb");
	char buffer[8192];
	size_t len;
	int error = 0;

	if (!fd) {
		log_file_error(opt.template_file);
		return 0;
	}

	rhash_data.template_text = rsh_str_new();

	while (!feof(fd)) {
		len = fread(buffer, 1, 8192, fd);
		if (ferror(fd)) break;

		rsh_str_append_n(rhash_data.template_text, buffer, len);
		if (rhash_data.template_text->len >= MAX_TEMPLATE_SIZE) {
			log_msg(_("%s: template file is too big\n"), opt.template_file);
			error = 1;
		}
	}

	if (ferror(fd)) {
		log_file_error(opt.template_file);
		error = 1;
	}

	fclose(fd);
	rhash_data.printf_str = rhash_data.template_text->str;
	return !error;
}
