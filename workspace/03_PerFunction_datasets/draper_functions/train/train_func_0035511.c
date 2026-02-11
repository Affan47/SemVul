xfs_dquot_buf_write_verify(
	struct xfs_buf	*bp)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;

	if (!xfs_dquot_buf_verify(mp, bp, XFS_QMOPT_DOWARN)) {
		xfs_buf_ioerror(bp, -EFSCORRUPTED);
		xfs_verifier_error(bp);
		return;
	}
}
