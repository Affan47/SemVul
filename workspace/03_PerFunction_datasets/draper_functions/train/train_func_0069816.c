au_wbr_create_rr(struct dentry *dentry, unsigned int flags)
{
	int err, nbr;
	unsigned int u;
	aufs_bindex_t bindex, bend;
	struct super_block *sb;
	atomic_t *next;

	err = au_wbr_create_exp(dentry);
	if (err >= 0)
		goto out;

	sb = dentry->d_sb;
	next = &au_sbi(sb)->si_wbr_rr_next;
	bend = au_sbend(sb);
	nbr = bend + 1;
	for (bindex = 0; bindex <= bend; bindex++) {
		if (!au_ftest_wbr(flags, DIR)) {
			err = atomic_dec_return(next) + 1;

			if (unlikely(!err))
				err = atomic_dec_return(next) + 1;
		} else
			err = atomic_read(next);
		AuDbg("%d\n", err);
		u = err;
		err = u % nbr;
		AuDbg("%d\n", err);
		if (!au_br_rdonly(au_sbr(sb, err)))
			break;
		err = -EROFS;
	}

	if (err >= 0)
		err = au_wbr_nonopq(dentry, err);

out:
	AuDbg("%d\n", err);
	return err;
}
