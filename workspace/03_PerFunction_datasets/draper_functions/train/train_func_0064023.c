write_tar_entry(const unsigned char *sha1,
                           const char *base, int baselen,
                           const char *filename, unsigned mode, int stage)
{
	static struct strbuf path;
	int filenamelen = strlen(filename);
	void *buffer;
	enum object_type type;
	unsigned long size;

	if (!path.alloc) {
		path.buf = xmalloc(PATH_MAX);
		path.alloc = PATH_MAX;
		path.len = path.eof = 0;
	}
	if (path.alloc < baselen + filenamelen + 1) {
		free(path.buf);
		path.buf = xmalloc(baselen + filenamelen + 1);
		path.alloc = baselen + filenamelen + 1;
	}
	memcpy(path.buf, base, baselen);
	memcpy(path.buf + baselen, filename, filenamelen);
	path.len = baselen + filenamelen;
	path.buf[path.len] = '\0';
	if (S_ISDIR(mode) || S_ISGITLINK(mode)) {
		strbuf_append_string(&path, "/");
		buffer = NULL;
		size = 0;
	} else {
		buffer = convert_sha1_file(path.buf, sha1, mode, &type, &size);
		if (!buffer)
			die("cannot read %s", sha1_to_hex(sha1));
	}

	write_entry(sha1, &path, mode, buffer, size);
	free(buffer);

	return READ_TREE_RECURSIVE;
}
