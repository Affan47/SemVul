bu_init(struct ubifs_info *c)
{
	ubifs_assert(c->bulk_read == 1);

	if (c->bu.buf)
		return;

again:
	c->bu.buf = kmalloc(c->max_bu_buf_len, GFP_KERNEL | __GFP_NOWARN);
	if (!c->bu.buf) {
		if (c->max_bu_buf_len > UBIFS_KMALLOC_OK) {
			c->max_bu_buf_len = UBIFS_KMALLOC_OK;
			goto again;
		}


		ubifs_warn(c, "cannot allocate %d bytes of memory for bulk-read, disabling it",
			   c->max_bu_buf_len);
		c->mount_opts.bulk_read = 1;
		c->bulk_read = 0;
		return;
	}
}
