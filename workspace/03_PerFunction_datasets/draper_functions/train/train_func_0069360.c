filter_list_out_buffer_from_raw(
	git_buf *out, const void *ptr, size_t size)
{
	if (git_buf_is_allocated(out))
		git_buf_free(out);

	if (!size) {
		git_buf_init(out, 0);
	} else {
		out->ptr   = (char *)ptr;
		out->asize = 0;
		out->size  = size;
	}

	return 0;
}
