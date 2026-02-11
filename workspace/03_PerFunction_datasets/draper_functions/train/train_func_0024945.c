au_h_path_to_set_attr(struct dentry *dentry,
				 struct au_icpup_args *a, struct path *h_path)
{
	int err;
	struct super_block *sb;

	sb = dentry->d_sb;
	a->udba = au_opt_udba(sb);

	if (d_unhashed(dentry))
		a->udba = AuOpt_UDBA_NONE;
	if (a->udba != AuOpt_UDBA_NONE) {
		AuDebugOn(IS_ROOT(dentry));
		err = au_reval_for_attr(dentry, au_sigen(sb));
		if (unlikely(err))
			goto out;
	}
	err = au_pin_and_icpup(dentry, NULL, a);
	if (unlikely(err < 0))
		goto out;

	h_path->dentry = a->h_path.dentry;
	h_path->mnt = au_sbr_mnt(sb, a->btgt);

out:
	return err;
}
