au_dpri_file(struct file *file)
{
	struct au_finfo *finfo;
	struct au_fidir *fidir;
	struct au_hfile *hfile;
	aufs_bindex_t bindex;
	int err;

	err = do_pri_file(-1, file);
	if (err
	    || IS_ERR_OR_NULL(file->f_path.dentry)
	    || !au_test_aufs(file->f_path.dentry->d_sb))
		return;

	finfo = au_fi(file);
	if (!finfo)
		return;
	if (finfo->fi_btop < 0)
		return;
	fidir = finfo->fi_hdir;
	if (!fidir)
		do_pri_file(finfo->fi_btop, finfo->fi_htop.hf_file);
	else
		for (bindex = finfo->fi_btop;
		     bindex >= 0 && bindex <= fidir->fd_bbot;
		     bindex++) {
			hfile = fidir->fd_hfile + bindex;
			do_pri_file(bindex, hfile ? hfile->hf_file : NULL);
		}
}
