print_binary_hunk(diff_print_info *pi, git_blob *old, git_blob *new)
{
	git_buf deflate = GIT_BUF_INIT, delta = GIT_BUF_INIT, *out = NULL;
	const void *old_data, *new_data;
	git_off_t old_data_len, new_data_len;
	unsigned long delta_data_len, inflated_len;
	const char *out_type = "literal";
	char *scan, *end;
	int error;

	old_data = old ? git_blob_rawcontent(old) : NULL;
	new_data = new ? git_blob_rawcontent(new) : NULL;

	old_data_len = old ? git_blob_rawsize(old) : 0;
	new_data_len = new ? git_blob_rawsize(new) : 0;


	if (!git__is_ulong(old_data_len) || !git__is_ulong(new_data_len))
		return GIT_EBUFS;

	out = &deflate;
	inflated_len = (unsigned long)new_data_len;

	if ((error = git_zstream_deflatebuf(
			out, new_data, (size_t)new_data_len)) < 0)
		goto done;


	if (!git__is_ulong((git_off_t)deflate.size)) {
		error = GIT_EBUFS;
		goto done;
	}

	if (old && new) {
		void *delta_data = git_delta(
			old_data, (unsigned long)old_data_len,
			new_data, (unsigned long)new_data_len,
			&delta_data_len, (unsigned long)deflate.size);

		if (delta_data) {
			error = git_zstream_deflatebuf(
				&delta, delta_data, (size_t)delta_data_len);

			git__free(delta_data);

			if (error < 0)
				goto done;

			if (delta.size < deflate.size) {
				out = &delta;
				out_type = "delta";
				inflated_len = delta_data_len;
			}
		}
	}

	git_buf_printf(pi->buf, "%s %lu\n", out_type, inflated_len);
	pi->line.num_lines++;

	for (scan = out->ptr, end = out->ptr + out->size; scan < end; ) {
		size_t chunk_len = end - scan;
		if (chunk_len > 52)
			chunk_len = 52;

		if (chunk_len <= 26)
			git_buf_putc(pi->buf, (char)chunk_len + 'A' - 1);
		else
			git_buf_putc(pi->buf, (char)chunk_len - 26 + 'a' - 1);

		git_buf_encode_base85(pi->buf, scan, chunk_len);
		git_buf_putc(pi->buf, '\n');

		if (git_buf_oom(pi->buf)) {
			error = -1;
			goto done;
		}

		scan += chunk_len;
		pi->line.num_lines++;
	}

done:
	git_buf_free(&deflate);
	git_buf_free(&delta);

	return error;
}
