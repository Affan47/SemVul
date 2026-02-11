xfs_bulkstat_ichunk_ra(
	struct xfs_mount		*mp,
	xfs_agnumber_t			agno,
	struct xfs_inobt_rec_incore	*irec)
{
	xfs_agblock_t			agbno;
	struct blk_plug			plug;
	int				blks_per_cluster;
	int				inodes_per_cluster;
	int				i;

	agbno = XFS_AGINO_TO_AGBNO(mp, irec->ir_startino);
	blks_per_cluster = xfs_icluster_size_fsb(mp);
	inodes_per_cluster = blks_per_cluster << mp->m_sb.sb_inopblog;

	blk_start_plug(&plug);
	for (i = 0; i < XFS_INODES_PER_CHUNK;
	     i += inodes_per_cluster, agbno += blks_per_cluster) {
		if (xfs_inobt_maskn(i, inodes_per_cluster) & ~irec->ir_free) {
			xfs_btree_reada_bufs(mp, agno, agbno, blks_per_cluster,
					     &xfs_inode_buf_ops);
		}
	}
	blk_finish_plug(&plug);
}
