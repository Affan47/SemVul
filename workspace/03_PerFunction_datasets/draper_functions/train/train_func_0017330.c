xfs_dqrele_inode(
	struct xfs_inode	*ip,
	int			flags,
	void			*args)
{

	if (ip == ip->i_mount->m_quotainfo->qi_uquotaip ||
	    ip == ip->i_mount->m_quotainfo->qi_gquotaip ||
	    ip == ip->i_mount->m_quotainfo->qi_pquotaip) {
		ASSERT(ip->i_udquot == NULL);
		ASSERT(ip->i_gdquot == NULL);
		ASSERT(ip->i_pdquot == NULL);
		return 0;
	}

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	if ((flags & XFS_UQUOTA_ACCT) && ip->i_udquot) {
		xfs_qm_dqrele(ip->i_udquot);
		ip->i_udquot = NULL;
	}
	if ((flags & XFS_GQUOTA_ACCT) && ip->i_gdquot) {
		xfs_qm_dqrele(ip->i_gdquot);
		ip->i_gdquot = NULL;
	}
	if ((flags & XFS_PQUOTA_ACCT) && ip->i_pdquot) {
		xfs_qm_dqrele(ip->i_pdquot);
		ip->i_pdquot = NULL;
	}
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	return 0;
}
