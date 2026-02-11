is_object_file(const char *fname)
{
	int i;
	int len;

	len = strlen(fname);
	if (len < 2) {
		return 0;
	}


	if (len >= 2 && fname[len - 2] == '.' && fname[len - 1] == 'o') {
		return 1;
	}


	for (i = len - 1; i >= 0; i--) {
		if (fname[i] == '.') {
			return 0;
		} else if (fname[i] == '-') {
			return 1;
		}
	}
	return 1;
}
