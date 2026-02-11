xfs_buf_submit(
	struct xfs_buf	*bp)
{
	trace_xfs_buf_submit(bp, _RET_IP_);

	ASSERT(!(bp->b_flags & _XBF_DELWRI_Q));
	ASSERT(bp->b_flags & XBF_ASYNC);


	if (XFS_FORCED_SHUTDOWN(bp->b_target->bt_mount)) {
		xfs_buf_ioerror(bp, -EIO);
		bp->b_flags &= ~XBF_DONE;
		xfs_buf_stale(bp);
		xfs_buf_ioend(bp);
		return;
	}

	if (bp->b_flags & XBF_WRITE)
		xfs_buf_wait_unpin(bp);


	bp->b_io_error = 0;


	xfs_buf_hold(bp);


	atomic_set(&bp->b_io_remaining, 1);
	_xfs_buf_ioapply(bp);


	if (atomic_dec_and_test(&bp->b_io_remaining) == 1) {
		if (bp->b_error)
			xfs_buf_ioend(bp);
		else
			xfs_buf_ioend_async(bp);
	}

	xfs_buf_rele(bp);

}
