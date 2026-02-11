extHint(struct inode *ip, s64 offset, xad_t * xp)
{
	struct super_block *sb = ip->i_sb;
	int nbperpage = JFS_SBI(sb)->nbperpage;
	s64 prev;
	int rc = 0;
	s64 xaddr;
	int xlen;
	int xflag;


	XADaddress(xp, 0);


	prev = ((offset & ~POFFSET) >> JFS_SBI(sb)->l2bsize) - nbperpage;


	if (prev < 0)
		goto out;

	rc = xtLookup(ip, prev, nbperpage, &xflag, &xaddr, &xlen, 0);

	if ((rc == 0) && xlen) {
		if (xlen != nbperpage) {
			jfs_error(ip->i_sb, "corrupt xtree\n");
			rc = -EIO;
		}
		XADaddress(xp, xaddr);
		XADlength(xp, xlen);
		XADoffset(xp, prev);


		xp->flag  = xflag & XAD_NOTRECORDED;
	} else
		rc = 0;

out:
	return (rc);
}
