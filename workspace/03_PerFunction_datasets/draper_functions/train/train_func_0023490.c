snapshot_write_finalize(struct snapshot_handle *handle)
{
	copy_last_highmem_page();

	page_key_write(handle->buffer);
	page_key_free();

	if (handle->cur > 1 && handle->cur > nr_meta_pages + nr_copy_pages) {
		memory_bm_free(&orig_bm, PG_UNSAFE_CLEAR);
		free_highmem_data();
	}
}
