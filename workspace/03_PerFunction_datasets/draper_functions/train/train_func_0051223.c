ubifs_lpt_end_commit(struct ubifs_info *c)
{
	int err;

	dbg_lp("");

	if (!c->lpt_cnext)
		return 0;

	err = write_cnodes(c);
	if (err)
		return err;

	mutex_lock(&c->lp_mutex);
	free_obsolete_cnodes(c);
	mutex_unlock(&c->lp_mutex);

	return 0;
}
