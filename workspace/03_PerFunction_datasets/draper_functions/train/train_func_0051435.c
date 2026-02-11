qnx6_dir_longfilename(struct inode *inode,
			struct qnx6_long_dir_entry *de,
			struct dir_context *ctx,
			unsigned de_inode)
{
	struct qnx6_long_filename *lf;
	struct super_block *s = inode->i_sb;
	struct qnx6_sb_info *sbi = QNX6_SB(s);
	struct page *page;
	int lf_size;

	if (de->de_size != 0xff) {


		pr_err("invalid direntry size (%i).\n", de->de_size);
		return 0;
	}
	lf = qnx6_longname(s, de, &page);
	if (IS_ERR(lf)) {
		pr_err("Error reading longname\n");
		return 0;
	}

	lf_size = fs16_to_cpu(sbi, lf->lf_size);

	if (lf_size > QNX6_LONG_NAME_MAX) {
		pr_debug("file %s\n", lf->lf_fname);
		pr_err("Filename too long (%i)\n", lf_size);
		qnx6_put_page(page);
		return 0;
	}


	if (!test_opt(s, MMI_FS) && fs32_to_cpu(sbi, de->de_checksum) !=
			qnx6_lfile_checksum(lf->lf_fname, lf_size))
		pr_info("long filename checksum error.\n");

	pr_debug("qnx6_readdir:%.*s inode:%u\n",
		 lf_size, lf->lf_fname, de_inode);
	if (!dir_emit(ctx, lf->lf_fname, lf_size, de_inode, DT_UNKNOWN)) {
		qnx6_put_page(page);
		return 0;
	}

	qnx6_put_page(page);

	return 1;
}
