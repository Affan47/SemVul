write_deflate(git_filebuf *file, const void *source, size_t len)
{
	int result = Z_OK;
	z_stream *zs = &file->zs;

	if (len > 0 || file->flush_mode == Z_FINISH) {
		zs->next_in = (void *)source;
		zs->avail_in = len;

		do {
			int have;

			zs->next_out = file->z_buf;
			zs->avail_out = file->buf_size;

            result = deflate(zs, file->flush_mode);
            assert(result != Z_STREAM_ERROR);

            have = file->buf_size - zs->avail_out;

			if (gitfo_write(file->fd, file->z_buf, have) < GIT_SUCCESS)
				return GIT_EOSERR;

        } while (zs->avail_out == 0);

		assert(zs->avail_in == 0);

		if (file->digest)
			git_hash_update(file->digest, source, len);
	}

	return GIT_SUCCESS;
}
