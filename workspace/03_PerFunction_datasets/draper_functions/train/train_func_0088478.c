write_local_name(bdaddr_t *bdaddr, const char *name)
{
	char filename[PATH_MAX + 1], str[249];
	int i;

	memset(str, 0, sizeof(str));
	for (i = 0; i < 248 && name[i]; i++)
		if ((unsigned char) name[i] < 32 || name[i] == 127)
			str[i] = '.';
		else
			str[i] = name[i];

	create_filename(filename, PATH_MAX, bdaddr, "config");

	create_file(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	return textfile_put(filename, "name", str);
}
