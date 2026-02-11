io_ctl_add_bitmap(struct btrfs_io_ctl *io_ctl, void *bitmap)
{
	if (!io_ctl->cur)
		return -ENOSPC;


	if (io_ctl->cur != io_ctl->orig) {
		io_ctl_set_crc(io_ctl, io_ctl->index - 1);
		if (io_ctl->index >= io_ctl->num_pages)
			return -ENOSPC;
		io_ctl_map_page(io_ctl, 0);
	}

	memcpy(io_ctl->cur, bitmap, PAGE_CACHE_SIZE);
	io_ctl_set_crc(io_ctl, io_ctl->index - 1);
	if (io_ctl->index < io_ctl->num_pages)
		io_ctl_map_page(io_ctl, 0);
	return 0;
}
