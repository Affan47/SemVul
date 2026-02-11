au_ii_refresh(struct inode *inode, int *update)
{
	int err, e;
	umode_t type;
	aufs_bindex_t bindex, new_bindex;
	struct super_block *sb;
	struct au_iinfo *iinfo;
	struct au_hinode *p, *q, tmp;

	IiMustWriteLock(inode);

	*update = 0;
	sb = inode->i_sb;
	type = inode->i_mode & S_IFMT;
	iinfo = au_ii(inode);
	err = au_ii_realloc(iinfo, au_sbend(sb) + 1);
	if (unlikely(err))
		goto out;

	AuDebugOn(iinfo->ii_bstart < 0);
	p = iinfo->ii_hinode + iinfo->ii_bstart;
	for (bindex = iinfo->ii_bstart; bindex <= iinfo->ii_bend;
	     bindex++, p++) {
		if (!p->hi_inode)
			continue;

		AuDebugOn(type != (p->hi_inode->i_mode & S_IFMT));
		new_bindex = au_br_index(sb, p->hi_id);
		if (new_bindex == bindex)
			continue;

		if (new_bindex < 0) {
			*update = 1;
			au_hiput(p);
			p->hi_inode = NULL;
			continue;
		}

		if (new_bindex < iinfo->ii_bstart)
			iinfo->ii_bstart = new_bindex;
		if (iinfo->ii_bend < new_bindex)
			iinfo->ii_bend = new_bindex;

		q = iinfo->ii_hinode + new_bindex;
		tmp = *q;
		*q = *p;
		*p = tmp;
		if (tmp.hi_inode) {
			bindex--;
			p--;
		}
	}
	au_update_ibrange(inode, 0);
	e = au_dy_irefresh(inode);
	if (unlikely(e && !err))
		err = e;

out:
	AuTraceErr(err);
	return err;
}
