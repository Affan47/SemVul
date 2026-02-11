au_di_alloc(struct super_block *sb, unsigned int lsc)
{
	struct au_dinfo *dinfo;
	int nbr, i;

	dinfo = au_cache_alloc_dinfo();
	if (unlikely(!dinfo))
		goto out;

	nbr = au_sbend(sb) + 1;
	if (nbr <= 0)
		nbr = 1;
	dinfo->di_hdentry = kcalloc(nbr, sizeof(*dinfo->di_hdentry), GFP_NOFS);
	if (dinfo->di_hdentry) {
		au_rw_write_lock_nested(&dinfo->di_rwsem, lsc);
		dinfo->di_bstart = -1;
		dinfo->di_bend = -1;
		dinfo->di_bwh = -1;
		dinfo->di_bdiropq = -1;
		dinfo->di_tmpfile = 0;
		for (i = 0; i < nbr; i++)
			dinfo->di_hdentry[i].hd_id = -1;
		goto out;
	}

	au_cache_free_dinfo(dinfo);
	dinfo = NULL;

out:
	return dinfo;
}
