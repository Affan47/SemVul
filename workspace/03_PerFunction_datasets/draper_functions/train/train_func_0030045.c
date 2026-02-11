xfs_dir3_free_hdr_to_disk(
	struct xfs_dir2_free		*to,
	struct xfs_dir3_icfree_hdr	*from)
{
	struct xfs_dir3_free_hdr *hdr3 = (struct xfs_dir3_free_hdr *)to;

	ASSERT(from->magic == XFS_DIR3_FREE_MAGIC);

	hdr3->hdr.magic = cpu_to_be32(from->magic);
	hdr3->firstdb = cpu_to_be32(from->firstdb);
	hdr3->nvalid = cpu_to_be32(from->nvalid);
	hdr3->nused = cpu_to_be32(from->nused);
}
