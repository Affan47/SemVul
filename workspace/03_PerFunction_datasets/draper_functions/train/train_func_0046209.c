cfs_fgets(char *s, int n, CHIRP_FILE * file)
{
	char *current = s;
	INT64_T i, empty = file->read_n == 0;

	if(file == &CHIRP_FILE_NULL)
		return NULL;

	for(i = 0; i < file->read_n; i++)
		if(i + 2 >= n || file->read[i] == '\n') {
			memcpy(s, file->read, i + 1);
			s[i + 1] = '\0';
			memmove(file->read, file->read + i + 1, (file->read_n -= i + 1));
			return s;
		}
	memcpy(current, file->read, i);
	current += i;
	n -= i;
	file->read_n = 0;

	i = cfs->pread(file->fd, file->read, CHIRP_FILESYSTEM_BUFFER - 1, file->offset);
	if(i == -1) {
		file->error = errno;
		return 0;
	} else if(i == 0 && empty) {
		return NULL;
	} else if(i == 0) {
		return s;
	}

	file->read_n += i;
	file->offset += i;

	if(cfs_fgets(current, n, file) == NULL)
		return NULL;
	else
		return s;
}
