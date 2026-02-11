dax_io(struct inode *inode, struct iov_iter *iter,
		      loff_t start, loff_t end, get_block_t get_block,
		      struct buffer_head *bh)
{
	ssize_t retval = 0;
	loff_t pos = start;
	loff_t max = start;
	loff_t bh_max = start;
	void __pmem *addr;
	bool hole = false;
	bool need_wmb = false;

	if (iov_iter_rw(iter) != WRITE)
		end = min(end, i_size_read(inode));

	while (pos < end) {
		size_t len;
		if (pos == max) {
			unsigned blkbits = inode->i_blkbits;
			long page = pos >> PAGE_SHIFT;
			sector_t block = page << (PAGE_SHIFT - blkbits);
			unsigned first = pos - (block << blkbits);
			long size;

			if (pos == bh_max) {
				bh->b_size = PAGE_ALIGN(end - pos);
				bh->b_state = 0;
				retval = get_block(inode, block, bh,
						   iov_iter_rw(iter) == WRITE);
				if (retval)
					break;
				if (!buffer_size_valid(bh))
					bh->b_size = 1 << blkbits;
				bh_max = pos - first + bh->b_size;
			} else {
				unsigned done = bh->b_size -
						(bh_max - (pos - first));
				bh->b_blocknr += done >> blkbits;
				bh->b_size -= done;
			}

			hole = iov_iter_rw(iter) != WRITE && !buffer_written(bh);
			if (hole) {
				addr = NULL;
				size = bh->b_size - first;
			} else {
				retval = dax_get_addr(bh, &addr, blkbits);
				if (retval < 0)
					break;
				if (buffer_unwritten(bh) || buffer_new(bh)) {
					dax_new_buf(addr, retval, first, pos,
									end);
					need_wmb = true;
				}
				addr += first;
				size = retval - first;
			}
			max = min(pos + size, end);
		}

		if (iov_iter_rw(iter) == WRITE) {
			len = copy_from_iter_pmem(addr, max - pos, iter);
			need_wmb = true;
		} else if (!hole)
			len = copy_to_iter((void __force *)addr, max - pos,
					iter);
		else
			len = iov_iter_zero(max - pos, iter);

		if (!len) {
			retval = -EFAULT;
			break;
		}

		pos += len;
		addr += len;
	}

	if (need_wmb)
		wmb_pmem();

	return (pos == start) ? retval : pos - start;
}
