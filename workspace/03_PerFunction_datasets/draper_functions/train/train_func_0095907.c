ubifs_tnc_bulk_read(struct ubifs_info *c, struct bu_info *bu)
{
	int lnum = bu->zbranch[0].lnum, offs = bu->zbranch[0].offs, len, err, i;
	struct ubifs_wbuf *wbuf;
	void *buf;

	len = bu->zbranch[bu->cnt - 1].offs;
	len += bu->zbranch[bu->cnt - 1].len - offs;
	if (len > bu->buf_len) {
		ubifs_err(c, "buffer too small %d vs %d", bu->buf_len, len);
		return -EINVAL;
	}


	wbuf = ubifs_get_wbuf(c, lnum);
	if (wbuf)
		err = read_wbuf(wbuf, bu->buf, len, lnum, offs);
	else
		err = ubifs_leb_read(c, lnum, bu->buf, offs, len, 0);


	if (maybe_leb_gced(c, lnum, bu->gc_seq))
		return -EAGAIN;

	if (err && err != -EBADMSG) {
		ubifs_err(c, "failed to read from LEB %d:%d, error %d",
			  lnum, offs, err);
		dump_stack();
		dbg_tnck(&bu->key, "key ");
		return err;
	}


	buf = bu->buf;
	for (i = 0; i < bu->cnt; i++) {
		err = validate_data_node(c, buf, &bu->zbranch[i]);
		if (err)
			return err;
		buf = buf + ALIGN(bu->zbranch[i].len, 8);
	}

	return 0;
}
