loopcxt_find_unused(struct loopdev_cxt *lc)
{
	int rc;

	rc = loopcxt_init_iterator(lc, LOOPITER_FL_FREE);
	if (rc)
		return rc;

	rc = loopcxt_next(lc);
	loopcxt_deinit_iterator(lc);

	return rc;
}
