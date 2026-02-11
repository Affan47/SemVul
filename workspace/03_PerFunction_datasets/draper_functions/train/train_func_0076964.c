ubifs_read_one_lp(struct ubifs_info *c, int lnum, struct ubifs_lprops *lp)
{
	int err = 0;
	const struct ubifs_lprops *lpp;

	ubifs_get_lprops(c);

	lpp = ubifs_lpt_lookup(c, lnum);
	if (IS_ERR(lpp)) {
		err = PTR_ERR(lpp);
		ubifs_err(c, "cannot read properties of LEB %d, error %d",
			  lnum, err);
		goto out;
	}

	memcpy(lp, lpp, sizeof(struct ubifs_lprops));

out:
	ubifs_release_lprops(c);
	return err;
}
