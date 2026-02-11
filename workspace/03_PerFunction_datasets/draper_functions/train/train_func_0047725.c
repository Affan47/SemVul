xfs_dir3_leaf_log_ents(
	struct xfs_da_args	*args,
	struct xfs_buf		*bp,
	int			first,
	int			last)
{
	xfs_dir2_leaf_entry_t	*firstlep;
	xfs_dir2_leaf_entry_t	*lastlep;
	struct xfs_dir2_leaf	*leaf = bp->b_addr;
	struct xfs_dir2_leaf_entry *ents;

	ASSERT(leaf->hdr.info.magic == cpu_to_be16(XFS_DIR2_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_DIR3_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_DIR2_LEAFN_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_DIR3_LEAFN_MAGIC));

	ents = args->dp->d_ops->leaf_ents_p(leaf);
	firstlep = &ents[first];
	lastlep = &ents[last];
	xfs_trans_log_buf(args->trans, bp,
		(uint)((char *)firstlep - (char *)leaf),
		(uint)((char *)lastlep - (char *)leaf + sizeof(*lastlep) - 1));
}
