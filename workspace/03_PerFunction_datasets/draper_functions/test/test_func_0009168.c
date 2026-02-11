gfs2_drop_inode(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);

	if (!test_bit(GIF_FREE_VFS_INODE, &ip->i_flags) && inode->i_nlink) {
		struct gfs2_glock *gl = ip->i_iopen_gh.gh_gl;
		if (gl && test_bit(GLF_DEMOTE, &gl->gl_flags))
			clear_nlink(inode);
	}
	return generic_drop_inode(inode);
}
