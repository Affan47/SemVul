check_contains(char *f, char *s)
{
	int ret = 0;
	FILE *where = open_file(f, 0);

	if (where) {
		char buf1[256];

		while (fgets(buf1, 256, where)) {
			if (strstr(buf1, s)) {
				ret = 1;
				break;
			}
		}
		fclose(where);
	} else {
		NORM_ERR("Could not open the file '%s'", f);
	}
	return ret;
}
