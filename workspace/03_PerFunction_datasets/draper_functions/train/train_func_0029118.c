find_header(struct outline_file *file, char *buf, size_t size, size_t *pread)
{
    while (fgets(buf, size, file->fp)) {
	size_t rdbytes = strlen(buf);
	size_t len = trimnl(buf);

	if (len > 0) {
	    int level;

	    for (level = 0; buf[level] == '*' && level < len; level++)
		;
	    if (level) {
		*pread = rdbytes;
		return level;
	    }
	}
    }
    return 0;
}
