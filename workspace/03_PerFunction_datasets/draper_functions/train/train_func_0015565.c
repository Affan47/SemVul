mtdswap_move_block(struct mtdswap_dev *d, unsigned int oldblock,
		unsigned int *newblock)
{
	struct mtd_info *mtd = d->mtd;
	struct swap_eb *eb, *oldeb;
	int ret;
	size_t retlen;
	unsigned int page, retries;
	loff_t readpos;

	page = d->revmap[oldblock];
	readpos = (loff_t) oldblock << PAGE_SHIFT;
	retries = 0;

retry:
	ret = mtd_read(mtd, readpos, PAGE_SIZE, &retlen, d->page_buf);

	if (ret < 0 && !mtd_is_bitflip(ret)) {
		oldeb = d->eb_data + oldblock / d->pages_per_eblk;
		oldeb->flags |= EBLOCK_READERR;

		dev_err(d->dev, "Read Error: %d (block %u)\n", ret,
			oldblock);
		retries++;
		if (retries < MTDSWAP_IO_RETRIES)
			goto retry;

		goto read_error;
	}

	if (retlen != PAGE_SIZE) {
		dev_err(d->dev, "Short read: %zd (block %u)\n", retlen,
		       oldblock);
		ret = -EIO;
		goto read_error;
	}

	ret = mtdswap_write_block(d, d->page_buf, page, newblock, 1);
	if (ret < 0) {
		d->page_data[page] = BLOCK_ERROR;
		dev_err(d->dev, "Write error: %d\n", ret);
		return ret;
	}

	eb = d->eb_data + *newblock / d->pages_per_eblk;
	d->page_data[page] = *newblock;
	d->revmap[oldblock] = PAGE_UNDEF;
	eb = d->eb_data + oldblock / d->pages_per_eblk;
	eb->active_count--;

	return 0;

read_error:
	d->page_data[page] = BLOCK_ERROR;
	d->revmap[oldblock] = PAGE_UNDEF;
	return ret;
}
