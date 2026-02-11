read_more(struct jffs2_sb_info *c, struct jffs2_raw_node_ref *ref,
		     int needed_len, int *rdlen, unsigned char *buf)
{
	int err, to_read = needed_len - *rdlen;
	size_t retlen;
	uint32_t offs;

	if (jffs2_is_writebuffered(c)) {
		int rem = to_read % c->wbuf_pagesize;

		if (rem)
			to_read += c->wbuf_pagesize - rem;
	}


	offs = ref_offset(ref) + *rdlen;

	dbg_readinode("read more %d bytes\n", to_read);

	err = jffs2_flash_read(c, offs, to_read, &retlen, buf + *rdlen);
	if (err) {
		JFFS2_ERROR("can not read %d bytes from 0x%08x, "
			"error code: %d.\n", to_read, offs, err);
		return err;
	}

	if (retlen < to_read) {
		JFFS2_ERROR("short read at %#08x: %zu instead of %d.\n",
				offs, retlen, to_read);
		return -EIO;
	}

	*rdlen += to_read;
	return 0;
}
