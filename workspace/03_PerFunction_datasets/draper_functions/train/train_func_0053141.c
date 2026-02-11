write_loose_object(const unsigned char *sha1, char *hdr, int hdrlen,
			      const void *buf, unsigned long len, time_t mtime)
{
	int fd, ret;
	unsigned char compressed[4096];
	z_stream stream;
	git_SHA_CTX c;
	unsigned char parano_sha1[20];
	char *filename;
	static char tmpfile[PATH_MAX];

	filename = sha1_file_name(sha1);
	fd = create_tmpfile(tmpfile, sizeof(tmpfile), filename);
	while (fd < 0 && errno == EMFILE && unuse_one_window(NULL, -1))
		fd = create_tmpfile(tmpfile, sizeof(tmpfile), filename);
	if (fd < 0) {
		if (errno == EACCES)
			return error("insufficient permission for adding an object to repository database %s\n", get_object_directory());
		else
			return error("unable to create temporary sha1 filename %s: %s\n", tmpfile, strerror(errno));
	}


	memset(&stream, 0, sizeof(stream));
	deflateInit(&stream, zlib_compression_level);
	stream.next_out = compressed;
	stream.avail_out = sizeof(compressed);
	git_SHA1_Init(&c);


	stream.next_in = (unsigned char *)hdr;
	stream.avail_in = hdrlen;
	while (deflate(&stream, 0) == Z_OK)
		;
	git_SHA1_Update(&c, hdr, hdrlen);


	stream.next_in = (void *)buf;
	stream.avail_in = len;
	do {
		unsigned char *in0 = stream.next_in;
		ret = deflate(&stream, Z_FINISH);
		git_SHA1_Update(&c, in0, stream.next_in - in0);
		if (write_buffer(fd, compressed, stream.next_out - compressed) < 0)
			die("unable to write sha1 file");
		stream.next_out = compressed;
		stream.avail_out = sizeof(compressed);
	} while (ret == Z_OK);

	if (ret != Z_STREAM_END)
		die("unable to deflate new object %s (%d)", sha1_to_hex(sha1), ret);
	ret = deflateEnd(&stream);
	if (ret != Z_OK)
		die("deflateEnd on object %s failed (%d)", sha1_to_hex(sha1), ret);
	git_SHA1_Final(parano_sha1, &c);
	if (hashcmp(sha1, parano_sha1) != 0)
		die("confused by unstable object source data for %s", sha1_to_hex(sha1));

	close_sha1_file(fd);

	if (mtime) {
		struct utimbuf utb;
		utb.actime = mtime;
		utb.modtime = mtime;
		if (utime(tmpfile, &utb) < 0)
			warning("failed utime() on %s: %s",
				tmpfile, strerror(errno));
	}

	return move_temp_to_file(tmpfile, filename);
}
