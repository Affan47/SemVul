au_wbr(struct dentry *dentry, aufs_bindex_t btgt)
{
	aufs_bindex_t bdiropq, bwh;
	struct dentry *parent;
	struct au_branch *br;

	parent = dentry->d_parent;
	IMustLock(d_inode(parent));

	bdiropq = au_dbdiropq(parent);
	bwh = au_dbwh(dentry);
	br = au_sbr(dentry->d_sb, btgt);
	if (au_br_rdonly(br)
	    || (0 <= bdiropq && bdiropq < btgt)
	    || (0 <= bwh && bwh < btgt))
		btgt = -1;

	AuDbg("btgt %d\n", btgt);
	return btgt;
}
