get_master_node(const struct ubifs_info *c, int lnum, void **pbuf,
			   struct ubifs_mst_node **mst, void **cor)
{
	const int sz = c->mst_node_alsz;
	int err, offs, len;
	void *sbuf, *buf;

	sbuf = vmalloc(c->leb_size);
	if (!sbuf)
		return -ENOMEM;

	err = ubifs_leb_read(c, lnum, sbuf, 0, c->leb_size, 0);
	if (err && err != -EBADMSG)
		goto out_free;


	offs = 0;
	buf = sbuf;
	len = c->leb_size;
	while (offs + UBIFS_MST_NODE_SZ <= c->leb_size) {
		struct ubifs_ch *ch = buf;

		if (le32_to_cpu(ch->magic) != UBIFS_NODE_MAGIC)
			break;
		offs += sz;
		buf  += sz;
		len  -= sz;
	}

	if (offs) {
		int ret;

		offs -= sz;
		buf  -= sz;
		len  += sz;
		ret = ubifs_scan_a_node(c, buf, len, lnum, offs, 1);
		if (ret != SCANNED_A_NODE && offs) {

			offs -= sz;
			buf  -= sz;
			len  += sz;
			ret = ubifs_scan_a_node(c, buf, len, lnum, offs, 1);
			if (ret != SCANNED_A_NODE)


				goto out_err;
		}
		if (ret == SCANNED_A_NODE) {
			struct ubifs_ch *ch = buf;

			if (ch->node_type != UBIFS_MST_NODE)
				goto out_err;
			dbg_rcvry("found a master node at %d:%d", lnum, offs);
			*mst = buf;
			offs += sz;
			buf  += sz;
			len  -= sz;
		}
	}

	if (offs < c->leb_size) {
		if (!is_empty(buf, min_t(int, len, sz))) {
			*cor = buf;
			dbg_rcvry("found corruption at %d:%d", lnum, offs);
		}
		offs += sz;
		buf  += sz;
		len  -= sz;
	}

	if (offs < c->leb_size)
		if (!is_empty(buf, len))
			goto out_err;
	*pbuf = sbuf;
	return 0;

out_err:
	err = -EINVAL;
out_free:
	vfree(sbuf);
	*mst = NULL;
	*cor = NULL;
	return err;
}
