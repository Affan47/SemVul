is_exe(char *filename)
{
	FILE *file;
	char buf[4];
	char header[] = {0x00, 0x00, 0x03, 0xf3};


	if (strstr(filename, ".exe") || strstr(filename, ".EXE")
	    || strstr(filename, ".prg") || strstr(filename, ".PRG"))
		return 1;


	if (strchr(filename, '.'))
		return 0;

	file = fopen(filename, "rb");
	if (!file)
		return 0;

	if (fread(buf, 1, 4, file) < 4) {
		fclose(file);
		return 0;
	}

	fclose(file);


	return memcmp(buf, header, 4) == 0;
}
