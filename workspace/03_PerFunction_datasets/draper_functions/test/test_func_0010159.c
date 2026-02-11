add_file_to_table(char *fname, int readonly)
{
	FILE *f;
	char buf[255];

	if ((f = fopen(fname, "r")) == NULL)
		err(1, "%s", fname);

	while (fgets(buf, 255, f) != NULL) {
		if (strlen(buf) > 1) {
			buf[strlen(buf) - 1] = '\0';
			if (readonly)
				add_ro_identifier(buf);
			else
				add_identifier(buf);
		}
	}

	fclose(f);
}
