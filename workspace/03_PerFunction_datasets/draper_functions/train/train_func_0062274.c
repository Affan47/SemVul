au_wh_init_rw(struct dentry *h_root, struct au_wbr *wbr,
			 int do_plink, struct au_wh_base base[],
			 struct path *h_path)
{
	int err;
	struct inode *h_dir;

	WbrWhMustWriteLock(wbr);

	err = test_linkable(h_root);
	if (unlikely(err)) {
		err = 1;
		goto out;
	}


	err = -EEXIST;
	h_dir = d_inode(h_root);
	if (d_is_negative(base[AuBrWh_BASE].dentry)) {
		h_path->dentry = base[AuBrWh_BASE].dentry;
		err = vfsub_create(h_dir, h_path, WH_MASK, true);
	} else if (d_is_reg(base[AuBrWh_BASE].dentry))
		err = 0;
	else
		pr_err("unknown %pd2 exists\n", base[AuBrWh_BASE].dentry);
	if (unlikely(err))
		goto out;

	h_path->dentry = base[AuBrWh_PLINK].dentry;
	if (do_plink) {
		err = au_whdir(h_dir, h_path);
		if (unlikely(err))
			goto out;
		wbr->wbr_plink = dget(base[AuBrWh_PLINK].dentry);
	} else
		au_wh_clean(h_dir, h_path, 1);
	wbr->wbr_whbase = dget(base[AuBrWh_BASE].dentry);

	h_path->dentry = base[AuBrWh_ORPH].dentry;
	err = au_whdir(h_dir, h_path);
	if (unlikely(err))
		goto out;
	wbr->wbr_orph = dget(base[AuBrWh_ORPH].dentry);

out:
	return err;
}
