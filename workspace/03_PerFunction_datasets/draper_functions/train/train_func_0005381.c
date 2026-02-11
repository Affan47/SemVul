gfs2_dirent_first(struct gfs2_inode *dip, struct gfs2_buffer_head *bh,
					  struct gfs2_dirent **dent)
{
	struct gfs2_meta_header *h = (struct gfs2_meta_header *)bh->b_data;

	if (be32_to_cpu(h->mh_type) == GFS2_METATYPE_LF) {
		*dent = (struct gfs2_dirent *)(bh->b_data + sizeof(struct gfs2_leaf));
		return IS_LEAF;
	} else {
		*dent = (struct gfs2_dirent *)(bh->b_data + sizeof(struct gfs2_dinode));
		return IS_DINODE;
	}
}
