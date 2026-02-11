xfs_log_release_iclog(
	struct xfs_mount	*mp,
	struct xlog_in_core	*iclog)
{
	if (xlog_state_release_iclog(mp->m_log, iclog)) {
		xfs_force_shutdown(mp, SHUTDOWN_LOG_IO_ERROR);
		return -EIO;
	}

	return 0;
}
