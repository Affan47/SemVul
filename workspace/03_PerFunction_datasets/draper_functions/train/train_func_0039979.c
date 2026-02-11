fillvdir(struct dir_context *ctx, const char *__name, int nlen,
		    loff_t offset __maybe_unused, u64 h_ino,
		    unsigned int d_type)
{
	struct fillvdir_arg *arg = container_of(ctx, struct fillvdir_arg, ctx);
	char *name = (void *)__name;
	struct super_block *sb;
	ino_t ino;
	const unsigned char shwh = !!au_ftest_fillvdir(arg->flags, SHWH);

	arg->err = 0;
	sb = arg->file->f_path.dentry->d_sb;
	au_fset_fillvdir(arg->flags, CALLED);

	if (nlen <= AUFS_WH_PFX_LEN
	    || memcmp(name, AUFS_WH_PFX, AUFS_WH_PFX_LEN)) {
		if (test_known(&arg->delist, name, nlen)
		    || au_nhash_test_known_wh(&arg->whlist, name, nlen))
			goto out;

		arg->err = au_ino(sb, arg->bindex, h_ino, d_type, &ino);
		if (!arg->err) {
			if (unlikely(nlen > AUFS_MAX_NAMELEN))
				d_type = DT_UNKNOWN;
			arg->err = append_de(arg->vdir, name, nlen, ino,
					     d_type, &arg->delist);
		}
	} else if (au_ftest_fillvdir(arg->flags, WHABLE)) {
		name += AUFS_WH_PFX_LEN;
		nlen -= AUFS_WH_PFX_LEN;
		if (au_nhash_test_known_wh(&arg->whlist, name, nlen))
			goto out;

		if (shwh)
			arg->err = au_wh_ino(sb, arg->bindex, h_ino, d_type,
					     &ino);
		if (!arg->err) {
			if (nlen <= AUFS_MAX_NAMELEN + AUFS_WH_PFX_LEN)
				d_type = DT_UNKNOWN;
			arg->err = au_nhash_append_wh
				(&arg->whlist, name, nlen, ino, d_type,
				 arg->bindex, shwh);
		}
	}

out:
	if (!arg->err)
		arg->vdir->vd_jiffy = jiffies;

	AuTraceErr(arg->err);
	return arg->err;
}
