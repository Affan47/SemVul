display_path(uint32_t inoidx, int inopfx, uint32_t ino_parent,
		 char *inopath, struct fsck_inode_record *ino_recptr)
{
	int dip_rc = FSCK_OK;

	if ((!ino_recptr->unxpctd_prnts)
	    || (!(ino_recptr->inode_type == directory_inode))) {

		if (ino_recptr->inode_type == directory_inode) {
			fsck_send_msg(fsck_INOPATHOK, fsck_ref_msg(fsck_directory),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		} else if (ino_recptr->inode_type == char_special_inode) {
			fsck_send_msg(fsck_INOPATHOK, fsck_ref_msg(fsck_char_special),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		} else if (ino_recptr->inode_type == block_special_inode) {
			fsck_send_msg(fsck_INOPATHOK, fsck_ref_msg(fsck_block_special),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		} else if (ino_recptr->inode_type == FIFO_inode) {
			fsck_send_msg(fsck_INOPATHOK, fsck_ref_msg(fsck_FIFO),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		} else if (ino_recptr->inode_type == SOCK_inode) {
			fsck_send_msg(fsck_INOPATHOK, fsck_ref_msg(fsck_SOCK),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		} else {

			fsck_send_msg(fsck_INOPATHOK, fsck_ref_msg(fsck_file),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		}
	} else {

		if (ino_parent == ino_recptr->parent_inonum) {

			fsck_send_msg(fsck_INOPATHCRCT, inopath,
				      fsck_ref_msg(inopfx), inoidx);
		} else {

			fsck_send_msg(fsck_INOPATHBAD, fsck_ref_msg(fsck_directory),
				      fsck_ref_msg(inopfx), inoidx, inopath);
		}
	}

	return (dip_rc);
}
