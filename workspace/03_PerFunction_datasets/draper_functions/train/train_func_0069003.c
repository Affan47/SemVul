test_dentry_busy(struct dentry *root, aufs_bindex_t bindex,
			    unsigned int sigen, const unsigned int verbose)
{
	int err, i, j, ndentry;
	aufs_bindex_t bstart, bend;
	struct au_dcsub_pages dpages;
	struct au_dpage *dpage;
	struct dentry *d;

	err = au_dpages_init(&dpages, GFP_NOFS);
	if (unlikely(err))
		goto out;
	err = au_dcsub_pages(&dpages, root, NULL, NULL);
	if (unlikely(err))
		goto out_dpages;

	for (i = 0; !err && i < dpages.ndpage; i++) {
		dpage = dpages.dpages + i;
		ndentry = dpage->ndentry;
		for (j = 0; !err && j < ndentry; j++) {
			d = dpage->dentries[j];
			AuDebugOn(au_dcount(d) <= 0);
			if (!au_digen_test(d, sigen)) {
				di_read_lock_child(d, AuLock_IR);
				if (unlikely(au_dbrange_test(d))) {
					di_read_unlock(d, AuLock_IR);
					continue;
				}
			} else {
				di_write_lock_child(d);
				if (unlikely(au_dbrange_test(d))) {
					di_write_unlock(d);
					continue;
				}
				err = au_reval_dpath(d, sigen);
				if (!err)
					di_downgrade_lock(d, AuLock_IR);
				else {
					di_write_unlock(d);
					break;
				}
			}


			bstart = au_dbstart(d);
			bend = au_dbend(d);
			if (bstart <= bindex
			    && bindex <= bend
			    && au_h_dptr(d, bindex)
			    && au_test_dbusy(d, bstart, bend)) {
				err = -EBUSY;
				AuVerbose(verbose, "busy %pd\n", d);
				AuDbgDentry(d);
			}
			di_read_unlock(d, AuLock_IR);
		}
	}

out_dpages:
	au_dpages_free(&dpages);
out:
	return err;
}
