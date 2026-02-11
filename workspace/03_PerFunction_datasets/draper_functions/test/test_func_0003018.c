xfs_dir2_leafn_lasthash(
	struct xfs_inode *dp,
	struct xfs_buf	*bp,
	int		*count)
{
	struct xfs_dir2_leaf	*leaf = bp->b_addr;
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_dir3_icleaf_hdr leafhdr;

	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);

	ASSERT(leafhdr.magic == XFS_DIR2_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_DIR3_LEAFN_MAGIC);

	if (count)
		*count = leafhdr.count;
	if (!leafhdr.count)
		return 0;

	ents = dp->d_ops->leaf_ents_p(leaf);
	return be32_to_cpu(ents[leafhdr.count - 1].hashval);
}
