process_directory(struct gfs2_sbd *sbp, uint64_t dirblock, uint64_t dentmod)
{
	struct gfs2_inode *dip;
	int error = 0;

	dip = lgfs2_inode_read(sbp, dirblock);
	if (dip == NULL)
		return -1;

	if (dip->i_di.di_flags & GFS2_DIF_EXHASH) {
		if (fix_one_directory_exhash(sbp, dip, dentmod)) {
			log_crit(_("Error fixing exhash directory.\n"));
			inode_put(&dip);
			return -1;
		}
	} else {
		error = process_dirent_info(dip, sbp, dip->i_bh, dip->i_di.di_entries, dentmod);
		if (error && error != -EISDIR) {
			log_crit(_("Error fixing linear directory.\n"));
			inode_put(&dip);
			return -1;
		}
	}
	bmodified(dip->i_bh);
	inode_put(&dip);
	return 0;
}
