xfs_dquot_buf_readahead_verify(
	struct xfs_buf	*bp)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;

	if (!xfs_dquot_buf_verify_crc(mp, bp) ||
	    !xfs_dquot_buf_verify(mp, bp, 0)) {
		xfs_buf_ioerror(bp, -EIO);
		bp->b_flags &= ~XBF_DONE;
	}
}
