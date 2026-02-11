xfs_dir2_data_freefind(
	struct xfs_dir2_data_hdr *hdr,
	struct xfs_dir2_data_free *bf,
	struct xfs_dir2_data_unused *dup)
{
	xfs_dir2_data_free_t	*dfp;
	xfs_dir2_data_aoff_t	off;
#ifdef DEBUG
	int			matched;
	int			seenzero;
#endif

	off = (xfs_dir2_data_aoff_t)((char *)dup - (char *)hdr);

#ifdef DEBUG


	ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_BLOCK_MAGIC));
	for (dfp = &bf[0], seenzero = matched = 0;
	     dfp < &bf[XFS_DIR2_DATA_FD_COUNT];
	     dfp++) {
		if (!dfp->offset) {
			ASSERT(!dfp->length);
			seenzero = 1;
			continue;
		}
		ASSERT(seenzero == 0);
		if (be16_to_cpu(dfp->offset) == off) {
			matched = 1;
			ASSERT(dfp->length == dup->length);
		} else if (off < be16_to_cpu(dfp->offset))
			ASSERT(off + be16_to_cpu(dup->length) <= be16_to_cpu(dfp->offset));
		else
			ASSERT(be16_to_cpu(dfp->offset) + be16_to_cpu(dfp->length) <= off);
		ASSERT(matched || be16_to_cpu(dfp->length) >= be16_to_cpu(dup->length));
		if (dfp > &bf[0])
			ASSERT(be16_to_cpu(dfp[-1].length) >= be16_to_cpu(dfp[0].length));
	}
#endif


	if (be16_to_cpu(dup->length) <
	    be16_to_cpu(bf[XFS_DIR2_DATA_FD_COUNT - 1].length))
		return NULL;


	for (dfp = &bf[0]; dfp < &bf[XFS_DIR2_DATA_FD_COUNT]; dfp++) {
		if (!dfp->offset)
			return NULL;
		if (be16_to_cpu(dfp->offset) == off)
			return dfp;
	}


	return NULL;
}
