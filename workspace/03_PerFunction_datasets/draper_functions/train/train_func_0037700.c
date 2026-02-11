ufs_sync_fs(struct super_block *sb, int wait)
{
	struct ufs_sb_private_info * uspi;
	struct ufs_super_block_first * usb1;
	struct ufs_super_block_third * usb3;
	unsigned flags;

	mutex_lock(&UFS_SB(sb)->s_lock);

	UFSD("ENTER\n");

	flags = UFS_SB(sb)->s_flags;
	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_first(uspi);
	usb3 = ubh_get_usb_third(uspi);

	usb1->fs_time = cpu_to_fs32(sb, get_seconds());
	if ((flags & UFS_ST_MASK) == UFS_ST_SUN  ||
	    (flags & UFS_ST_MASK) == UFS_ST_SUNOS ||
	    (flags & UFS_ST_MASK) == UFS_ST_SUNx86)
		ufs_set_fs_state(sb, usb1, usb3,
				UFS_FSOK - fs32_to_cpu(sb, usb1->fs_time));
	ufs_put_cstotal(sb);

	UFSD("EXIT\n");
	mutex_unlock(&UFS_SB(sb)->s_lock);

	return 0;
}
