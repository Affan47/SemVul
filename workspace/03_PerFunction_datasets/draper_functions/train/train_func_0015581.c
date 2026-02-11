ocfs2_handle_error(struct super_block *sb)
{
	struct ocfs2_super *osb = OCFS2_SB(sb);
	int rv = 0;

	ocfs2_set_osb_flag(osb, OCFS2_OSB_ERROR_FS);
	pr_crit("On-disk corruption discovered. "
		"Please run fsck.ocfs2 once the filesystem is unmounted.\n");

	if (osb->s_mount_opt & OCFS2_MOUNT_ERRORS_PANIC) {
		panic("OCFS2: (device %s): panic forced after error\n",
		      sb->s_id);
	} else if (osb->s_mount_opt & OCFS2_MOUNT_ERRORS_CONT) {
		pr_crit("OCFS2: Returning error to the calling process.\n");
		rv = -EIO;
	} else {
		rv = -EROFS;
		if (sb->s_flags & MS_RDONLY &&
				(ocfs2_is_soft_readonly(osb) ||
				 ocfs2_is_hard_readonly(osb)))
			return rv;

		pr_crit("OCFS2: File system is now read-only.\n");
		sb->s_flags |= MS_RDONLY;
		ocfs2_set_ro_flag(osb, 0);
	}

	return rv;
}
