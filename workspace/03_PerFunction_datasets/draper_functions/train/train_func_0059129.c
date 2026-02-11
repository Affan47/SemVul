loose_backend__write(git_oid *oid, git_odb_backend *_backend, const void *data, size_t len, git_otype type)
{
	int error = 0, header_len;
	git_buf final_path = GIT_BUF_INIT;
	char header[64];
	git_filebuf fbuf = GIT_FILEBUF_INIT;
	loose_backend *backend;

	backend = (loose_backend *)_backend;


	header_len = format_object_header(header, sizeof(header), len, type);

	if (git_buf_joinpath(&final_path, backend->objects_dir, "tmp_object") < 0 ||
		git_filebuf_open(&fbuf, final_path.ptr,
			GIT_FILEBUF_HASH_CONTENTS |
			GIT_FILEBUF_TEMPORARY |
			(backend->object_zlib_level << GIT_FILEBUF_DEFLATE_SHIFT)) < 0)
	{
		error = -1;
		goto cleanup;
	}

	git_filebuf_write(&fbuf, header, header_len);
	git_filebuf_write(&fbuf, data, len);
	git_filebuf_hash(oid, &fbuf);

	if (object_file_name(&final_path, backend->objects_dir, oid) < 0 ||
		git_futils_mkpath2file(final_path.ptr, GIT_OBJECT_DIR_MODE) < 0 ||
		git_filebuf_commit_at(&fbuf, final_path.ptr, GIT_OBJECT_FILE_MODE) < 0)
		error = -1;

cleanup:
	if (error < 0)
		git_filebuf_cleanup(&fbuf);
	git_buf_free(&final_path);
	return error;
}
