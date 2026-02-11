qnx6_long_match(int len, const char *name,
			struct qnx6_long_dir_entry *de, struct inode *dir)
{
	struct super_block *s = dir->i_sb;
	struct qnx6_sb_info *sbi = QNX6_SB(s);
	struct page *page;
	int thislen;
	struct qnx6_long_filename *lf = qnx6_longname(s, de, &page);

	if (IS_ERR(lf))
		return 0;

	thislen = fs16_to_cpu(sbi, lf->lf_size);
	if (len != thislen) {
		qnx6_put_page(page);
		return 0;
	}
	if (memcmp(name, lf->lf_fname, len) == 0) {
		qnx6_put_page(page);
		return fs32_to_cpu(sbi, de->de_inode);
	}
	qnx6_put_page(page);
	return 0;
}
