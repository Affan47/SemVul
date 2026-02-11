sha1_loose_object_info(const unsigned char *sha1, unsigned long *sizep)
{
	int status;
	unsigned long mapsize, size;
	void *map;
	z_stream stream;
	char hdr[32];

	map = map_sha1_file(sha1, &mapsize);
	if (!map)
		return error("unable to find %s", sha1_to_hex(sha1));
	if (unpack_sha1_header(&stream, map, mapsize, hdr, sizeof(hdr)) < 0)
		status = error("unable to unpack %s header",
			       sha1_to_hex(sha1));
	else if ((status = parse_sha1_header(hdr, &size)) < 0)
		status = error("unable to parse %s header", sha1_to_hex(sha1));
	else if (sizep)
		*sizep = size;
	git_inflate_end(&stream);
	munmap(map, mapsize);
	return status;
}
