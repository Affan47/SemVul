xfs_symlink_write_verify(
	struct xfs_buf	*bp)
{
	struct xfs_mount *mp = bp->b_target->bt_mount;
	struct xfs_buf_log_item	*bip = bp->b_fspriv;


	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return;

	if (!xfs_symlink_verify(bp)) {
		xfs_buf_ioerror(bp, -EFSCORRUPTED);
		xfs_verifier_error(bp);
		return;
	}

	if (bip) {
		struct xfs_dsymlink_hdr *dsl = bp->b_addr;
		dsl->sl_lsn = cpu_to_be64(bip->bli_item.li_lsn);
	}
	xfs_buf_update_cksum(bp, XFS_SYMLINK_CRC_OFF);
}
