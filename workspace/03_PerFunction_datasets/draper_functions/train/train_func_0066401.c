dbg_leb_write(struct ubifs_info *c, int lnum, const void *buf,
		  int offs, int len)
{
	int err, failing;

	if (dbg_is_power_cut(c))
		return -EROFS;

	failing = power_cut_emulated(c, lnum, 1);
	if (failing) {
		len = corrupt_data(c, buf, len);
		ubifs_warn(c, "actually write %d bytes to LEB %d:%d (the buffer was corrupted)",
			   len, lnum, offs);
	}
	err = ubi_leb_write(c->ubi, lnum, buf, offs, len);
	if (err)
		return err;
	if (failing)
		return -EROFS;
	return 0;
}
