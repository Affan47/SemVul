read_file_timestamp(FILE *fstream)
{
	struct stat data;

	if (fstat(fileno(fstream), &data) != 0) {
		return (unsigned int) -1;
	}

	return (unsigned int) data.st_mtime;
}
