mnt_free_update(struct libmnt_update *upd)
{
	if (!upd)
		return;

	DBG(UPDATE, mnt_debug_h(upd, "free"));

	mnt_free_fs(upd->fs);
	mnt_free_table(upd->mountinfo);
	free(upd->target);
	free(upd->filename);
	free(upd);
}
