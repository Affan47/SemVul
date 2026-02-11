xfs_vm_kill_delalloc_range(
	struct inode		*inode,
	loff_t			start,
	loff_t			end)
{
	struct xfs_inode	*ip = XFS_I(inode);
	xfs_fileoff_t		start_fsb;
	xfs_fileoff_t		end_fsb;
	int			error;

	start_fsb = XFS_B_TO_FSB(ip->i_mount, start);
	end_fsb = XFS_B_TO_FSB(ip->i_mount, end);
	if (end_fsb <= start_fsb)
		return;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	error = xfs_bmap_punch_delalloc_range(ip, start_fsb,
						end_fsb - start_fsb);
	if (error) {

		if (!XFS_FORCED_SHUTDOWN(ip->i_mount)) {
			xfs_alert(ip->i_mount,
		"xfs_vm_write_failed: unable to clean up ino %lld",
					ip->i_ino);
		}
	}
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
}
