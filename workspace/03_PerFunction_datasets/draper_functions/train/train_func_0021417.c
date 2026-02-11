read_header_loose(git_rawobj *out, const char *loc)
{
	int error = GIT_SUCCESS, z_return = Z_ERRNO, read_bytes;
	git_file fd;
	z_stream zs;
	obj_hdr header_obj;
	unsigned char raw_buffer[16], inflated_buffer[64];

	assert(out && loc);

	out->data = NULL;

	if ((fd = gitfo_open(loc, O_RDONLY)) < 0)
		return GIT_ENOTFOUND;

	init_stream(&zs, inflated_buffer, sizeof(inflated_buffer));

	if (inflateInit(&zs) < Z_OK) {
		error = GIT_EZLIB;
		goto cleanup;
	}

	do {
		if ((read_bytes = read(fd, raw_buffer, sizeof(raw_buffer))) > 0) {
			set_stream_input(&zs, raw_buffer, read_bytes);
			z_return = inflate(&zs, 0);
		} else {
			z_return = Z_STREAM_END;
			break;
		}
	} while (z_return == Z_OK);

	if ((z_return != Z_STREAM_END && z_return != Z_BUF_ERROR)
		|| get_object_header(&header_obj, inflated_buffer) == 0
		|| git_object_typeisloose(header_obj.type) == 0) {
		error = GIT_EOBJCORRUPTED;
		goto cleanup;
	}

	out->len  = header_obj.size;
	out->type = header_obj.type;

cleanup:
	finish_inflate(&zs);
	gitfo_close(fd);
	return error;
}
