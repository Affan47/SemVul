read_data(FILE *fin, void *buff, int size)
{
	int err;

	err = fread(buff, 1, size, fin);
	if (!err)
		return 1;
	if (err != size) {
		error("Cannot read profile file at pos %ld\n", ftell(fin));
		return -1;
	}
	return 0;
}
