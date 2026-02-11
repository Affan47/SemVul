ubifs_tnc_end_commit(struct ubifs_info *c)
{
	int err;

	if (!c->cnext)
		return 0;

	err = return_gap_lebs(c);
	if (err)
		return err;

	err = write_index(c);
	if (err)
		return err;

	mutex_lock(&c->tnc_mutex);

	dbg_cmt("TNC height is %d", c->zroot.znode->level + 1);

	free_obsolete_znodes(c);

	c->cnext = NULL;
	kfree(c->ilebs);
	c->ilebs = NULL;

	mutex_unlock(&c->tnc_mutex);

	return 0;
}
