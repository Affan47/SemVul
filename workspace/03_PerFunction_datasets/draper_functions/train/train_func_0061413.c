dirent_next(struct gfs2_inode *dip, struct buffer_head *bh,
		       struct gfs2_dirent **dent)
{
	struct gfs2_dirent *cur = *dent, *tmp;
	char *bh_end = bh->b_data + bh->b_size;
	int ret;

	ret = dirent_check_reclen(dip, cur, bh_end);
	if (ret < 0)
		return ret;

	tmp = (void *)cur + ret;
	ret = dirent_check_reclen(dip, tmp, bh_end);
	if (ret == -EIO)
		return ret;


	if (gfs2_dirent_sentinel(tmp)) {
		gfs2_consist_inode(dip);
		return -EIO;
	}

	*dent = tmp;
	return 0;
}
