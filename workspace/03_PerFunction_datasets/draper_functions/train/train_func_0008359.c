cpio_mkfile(const char *name, const char *location,
			unsigned int mode, uid_t uid, gid_t gid,
			unsigned int nlinks)
{
	char s[256];
	char *filebuf = NULL;
	struct stat buf;
	long size;
	int file = -1;
	int retval;
	int rc = -1;
	int namesize;
	int i;

	mode |= S_IFREG;

	retval = stat (location, &buf);
	if (retval) {
		fprintf (stderr, "File %s could not be located\n", location);
		goto error;
	}

	file = open (location, O_RDONLY);
	if (file < 0) {
		fprintf (stderr, "File %s could not be opened for reading\n", location);
		goto error;
	}

	filebuf = malloc(buf.st_size);
	if (!filebuf) {
		fprintf (stderr, "out of memory\n");
		goto error;
	}

	retval = read (file, filebuf, buf.st_size);
	if (retval < 0) {
		fprintf (stderr, "Can not read %s file\n", location);
		goto error;
	}

	size = 0;
	for (i = 1; i <= nlinks; i++) {

		if (i == nlinks) size = buf.st_size;

		namesize = strlen(name) + 1;
		sprintf(s,"%s%08X%08X%08lX%08lX%08X%08lX"
		       "%08lX%08X%08X%08X%08X%08X%08X",
			"070701",
			ino,
			mode,
			(long) uid,
			(long) gid,
			nlinks,
			(long) buf.st_mtime,
			size,
			3,
			1,
			0,
			0,
			namesize,
			0);
		push_hdr(s);
		push_string(name);
		push_pad();

		if (size) {
			fwrite(filebuf, size, 1, stdout);
			offset += size;
			push_pad();
		}

		name += namesize;
	}
	ino++;
	rc = 0;

error:
	if (filebuf) free(filebuf);
	if (file >= 0) close(file);
	return rc;
}
