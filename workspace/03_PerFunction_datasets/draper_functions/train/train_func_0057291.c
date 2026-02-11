xfs_dir3_leaf_hdr_from_disk(
	struct xfs_dir3_icleaf_hdr	*to,
	struct xfs_dir2_leaf		*from)
{
	struct xfs_dir3_leaf_hdr *hdr3 = (struct xfs_dir3_leaf_hdr *)from;

	to->forw = be32_to_cpu(hdr3->info.hdr.forw);
	to->back = be32_to_cpu(hdr3->info.hdr.back);
	to->magic = be16_to_cpu(hdr3->info.hdr.magic);
	to->count = be16_to_cpu(hdr3->count);
	to->stale = be16_to_cpu(hdr3->stale);

	ASSERT(to->magic == XFS_DIR3_LEAF1_MAGIC ||
	       to->magic == XFS_DIR3_LEAFN_MAGIC);
}
