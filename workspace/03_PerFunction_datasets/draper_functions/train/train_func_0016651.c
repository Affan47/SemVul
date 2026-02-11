nfs_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	unsigned offset = pos & (PAGE_CACHE_SIZE - 1);
	struct nfs_open_context *ctx = nfs_file_open_context(file);
	int status;

	dfprintk(PAGECACHE, "NFS: write_end(%pD2(%lu), %u@%lld)\n",
		file, mapping->host->i_ino, len, (long long) pos);


	if (!PageUptodate(page)) {
		unsigned pglen = nfs_page_length(page);
		unsigned end = offset + copied;

		if (pglen == 0) {
			zero_user_segments(page, 0, offset,
					end, PAGE_CACHE_SIZE);
			SetPageUptodate(page);
		} else if (end >= pglen) {
			zero_user_segment(page, end, PAGE_CACHE_SIZE);
			if (offset == 0)
				SetPageUptodate(page);
		} else
			zero_user_segment(page, pglen, PAGE_CACHE_SIZE);
	}

	status = nfs_updatepage(file, page, offset, copied);

	unlock_page(page);
	page_cache_release(page);

	if (status < 0)
		return status;
	NFS_I(mapping->host)->write_io += copied;

	if (nfs_ctx_key_to_expire(ctx)) {
		status = nfs_wb_all(mapping->host);
		if (status < 0)
			return status;
	}

	return copied;
}
