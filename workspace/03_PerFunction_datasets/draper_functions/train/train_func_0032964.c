xfs_verifier_error(
	struct xfs_buf		*bp)
{
	struct xfs_mount *mp = bp->b_target->bt_mount;

	xfs_alert(mp, "Metadata %s detected at %pF, %s block 0x%llx",
		  bp->b_error == -EFSBADCRC ? "CRC error" : "corruption",
		  __return_address, bp->b_ops->name, bp->b_bn);

	xfs_alert(mp, "Unmount and run xfs_repair");

	if (xfs_error_level >= XFS_ERRLEVEL_LOW) {
		xfs_alert(mp, "First 64 bytes of corrupted metadata buffer:");
		xfs_hex_dump(xfs_buf_offset(bp, 0), 64);
	}

	if (xfs_error_level >= XFS_ERRLEVEL_HIGH)
		xfs_stack_trace();
}
