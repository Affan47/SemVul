writefile(char *filename, char *text, int mode)
{
	FILE *file;

	mode = askoverwrite(filename, mode);


	if (mode == 2)
		file = fopen(filename, "a");

	else
		file = fopen(filename, "w");

	if (!file) {
		fprintf(stderr, _("Can't open file %s for writing!\n"),  filename);
		return -1;
	}
	fprintf(file, "%s\n", text);
	fclose(file);

	return 2;
}
