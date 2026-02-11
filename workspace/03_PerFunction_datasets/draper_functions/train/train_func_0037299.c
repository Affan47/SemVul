au_do_stfs(const unsigned char dmsg, struct au_mvd_args *a)
{
	int err;
	struct au_branch *br;

	a->mvdown.flags |= AUFS_MVDOWN_STFS_FAILED;
	br = au_sbr(a->sb, a->mvd_bsrc);
	err = au_br_stfs(br, &a->mvdown.stbr[AUFS_MVDOWN_UPPER].stfs);
	if (!err) {
		br = au_sbr(a->sb, a->mvd_bdst);
		a->mvdown.stbr[AUFS_MVDOWN_LOWER].brid = br->br_id;
		err = au_br_stfs(br, &a->mvdown.stbr[AUFS_MVDOWN_LOWER].stfs);
	}
	if (!err)
		a->mvdown.flags &= ~AUFS_MVDOWN_STFS_FAILED;
	else
		AU_MVD_PR(dmsg, "statfs failed (%d), ignored\n", err);
}
