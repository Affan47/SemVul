ufs_show_options(struct seq_file *seq, struct dentry *root)
{
	struct ufs_sb_info *sbi = UFS_SB(root->d_sb);
	unsigned mval = sbi->s_mount_opt & UFS_MOUNT_UFSTYPE;
	const struct match_token *tp = tokens;

	while (tp->token != Opt_onerror_panic && tp->token != mval)
		++tp;
	BUG_ON(tp->token == Opt_onerror_panic);
	seq_printf(seq, ",%s", tp->pattern);

	mval = sbi->s_mount_opt & UFS_MOUNT_ONERROR;
	while (tp->token != Opt_err && tp->token != mval)
		++tp;
	BUG_ON(tp->token == Opt_err);
	seq_printf(seq, ",%s", tp->pattern);

	return 0;
}
