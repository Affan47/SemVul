ocfs2_new_dir_wants_trailer(struct inode *dir)
{
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);

	return ocfs2_meta_ecc(osb) ||
		ocfs2_supports_indexed_dirs(osb);
}
