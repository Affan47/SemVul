swap_read_page(struct swap_map_handle *handle, void *buf,
		struct hib_bio_batch *hb)
{
	sector_t offset;
	int error;
	struct swap_map_page_list *tmp;

	if (!handle->cur)
		return -EINVAL;
	offset = handle->cur->entries[handle->k];
	if (!offset)
		return -EFAULT;
	error = hib_submit_io(READ_SYNC, offset, buf, hb);
	if (error)
		return error;
	if (++handle->k >= MAP_PAGE_ENTRIES) {
		handle->k = 0;
		free_page((unsigned long)handle->maps->map);
		tmp = handle->maps;
		handle->maps = handle->maps->next;
		kfree(tmp);
		if (!handle->maps)
			release_swap_reader(handle);
		else
			handle->cur = handle->maps->map;
	}
	return error;
}
