io_ctl_read_bitmap(struct btrfs_io_ctl *io_ctl,
			      struct btrfs_free_space *entry)
{
	int ret;

	ret = io_ctl_check_crc(io_ctl, io_ctl->index);
	if (ret)
		return ret;

	memcpy(entry->bitmap, io_ctl->cur, PAGE_CACHE_SIZE);
	io_ctl_unmap_page(io_ctl);

	return 0;
}
