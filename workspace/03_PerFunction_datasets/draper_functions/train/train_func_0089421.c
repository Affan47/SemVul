parse_file(const char *fname, struct md4_ctx *md)
{
	char *file;
	unsigned long i, len;

	file = grab_file(fname, &len);
	if (!file)
		return 0;

	for (i = 0; i < len; i++) {

		if (file[i] == '\\' && (i+1 < len) && file[i+1] == '\n') {
			i++;
			continue;
		}


		if (isspace(file[i]))
			continue;


		if (file[i] == '"') {
			i += parse_string(file+i, len - i, md);
			continue;
		}


		if (file[i] == '/' && file[i+1] == '*') {
			i += parse_comment(file+i, len - i);
			continue;
		}

		add_char(file[i], md);
	}
	release_file(file, len);
	return 1;
}
