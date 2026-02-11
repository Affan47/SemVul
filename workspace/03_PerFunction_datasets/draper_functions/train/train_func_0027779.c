nfs_pageio_cond_complete(struct nfs_pageio_descriptor *desc, pgoff_t index)
{
	struct nfs_pgio_mirror *mirror;
	struct nfs_page *prev;
	u32 midx;

	for (midx = 0; midx < desc->pg_mirror_count; midx++) {
		mirror = &desc->pg_mirrors[midx];
		if (!list_empty(&mirror->pg_list)) {
			prev = nfs_list_entry(mirror->pg_list.prev);
			if (index != prev->wb_index + 1)
				nfs_pageio_complete_mirror(desc, midx);
		}
	}
}
