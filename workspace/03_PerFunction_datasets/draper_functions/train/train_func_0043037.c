ceph_sync_read(struct kiocb *iocb, struct iov_iter *i,
				int *checkeof)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file_inode(file);
	struct page **pages;
	u64 off = iocb->ki_pos;
	int num_pages, ret;
	size_t len = iov_iter_count(i);

	dout("sync_read on file %p %llu~%u %s\n", file, off,
	     (unsigned)len,
	     (file->f_flags & O_DIRECT) ? "O_DIRECT" : "");

	if (!len)
		return 0;


	ret = filemap_write_and_wait_range(inode->i_mapping, off,
						off + len);
	if (ret < 0)
		return ret;

	if (iocb->ki_flags & IOCB_DIRECT) {
		while (iov_iter_count(i)) {
			size_t start;
			ssize_t n;

			n = dio_get_pagev_size(i);
			pages = dio_get_pages_alloc(i, n, &start, &num_pages);
			if (IS_ERR(pages))
				return PTR_ERR(pages);

			ret = striped_read(inode, off, n,
					   pages, num_pages, checkeof,
					   1, start);

			ceph_put_page_vector(pages, num_pages, true);

			if (ret <= 0)
				break;
			off += ret;
			iov_iter_advance(i, ret);
			if (ret < n)
				break;
		}
	} else {
		num_pages = calc_pages_for(off, len);
		pages = ceph_alloc_page_vector(num_pages, GFP_KERNEL);
		if (IS_ERR(pages))
			return PTR_ERR(pages);
		ret = striped_read(inode, off, len, pages,
					num_pages, checkeof, 0, 0);
		if (ret > 0) {
			int l, k = 0;
			size_t left = ret;

			while (left) {
				size_t page_off = off & ~PAGE_MASK;
				size_t copy = min_t(size_t,
						    PAGE_SIZE - page_off, left);
				l = copy_page_to_iter(pages[k++], page_off,
						      copy, i);
				off += l;
				left -= l;
				if (l < copy)
					break;
			}
		}
		ceph_release_page_vector(pages, num_pages);
	}

	if (off > iocb->ki_pos) {
		ret = off - iocb->ki_pos;
		iocb->ki_pos = off;
	}

	dout("sync_read result %d\n", ret);
	return ret;
}
