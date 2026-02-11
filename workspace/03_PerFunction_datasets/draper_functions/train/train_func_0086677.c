do_usermodehelper_file(const char *filename, int cap_ordinal)
{
	uint32_t lo32, hi32;
	FILE *file;
	static const size_t buf_size = 80;
	char buf[buf_size];
	char tail;
	size_t bytes_read;
	int ret;


	file = fopen(filename, "r+");
	if (!file && errno == ENOENT)
		fail("Could not disable usermode helpers capabilities as "
		     "%s is not available\n", filename);
	if (!file)
		fail("Failed to access file %s errno %d\n", filename, errno);


	bytes_read = fread(buf, 1, buf_size - 1, file);
	if (bytes_read == 0)
		fail("Trouble reading %s\n", filename);
	buf[bytes_read] = '\0';
	ret = sscanf(buf, "%u %u %c", &lo32, &hi32, &tail);
	if (ret != 2)
		fail("Failed to understand %s \"%s\"\n", filename, buf);


	if (cap_ordinal < 32)
		lo32 &= ~(1 << cap_ordinal);
	else
		hi32 &= ~(1 << (cap_ordinal - 32));


	ret = fflush(file);
	if (ret != 0)
		fail("Failed on file %s to fflush %d\n", filename, ret);
	sprintf(buf, "%u %u", lo32, hi32);
	ret = fwrite(buf, 1, strlen(buf) + 1, file);
	if (ret != 0)
		fail("Failed to commit usermode helper bitmasks: %d\n", ret);


	fclose(file);
}
