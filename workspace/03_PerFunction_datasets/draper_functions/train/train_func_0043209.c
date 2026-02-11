calc_map_size(int64_t number_of_blocks,
		  struct dinode *aggr_inodes,
		  int aggr_block_size, int *ag_size, unsigned inostamp)
{
	int rc = 0;
	int64_t npages, ndmaps, nl0pages;
	int64_t nb_diskmap;
	int64_t size_of_map;
	int64_t location;


	npages = ndmaps = ((number_of_blocks + BPERDMAP - 1) >> L2BPERDMAP) + 1;


	if ((((int64_t) ndmaps) << L2BPERDMAP) > MAXMAPSIZE)
		return (EINVAL);


	nl0pages = (ndmaps + LPERCTL - 1) >> L2LPERCTL;
	npages += nl0pages;

	if (nl0pages > 1) {

		npages += 1 + ((nl0pages + LPERCTL - 1) >> L2LPERCTL);
	} else {

		npages += 2;
	}


	npages++;


	size_of_map = npages << L2PSIZE;
	nb_diskmap = size_of_map / aggr_block_size;
	location = BMAP_OFF / aggr_block_size;

	init_inode(&(aggr_inodes[BMAP_I]), AGGREGATE_I,
		   BMAP_I,
		   nb_diskmap,
		   size_of_map,
		   location, IFJOURNAL | IFREG,
		   max_extent_data, AITBL_OFF / aggr_block_size,
		   aggr_block_size, inostamp);


	if ((rc = alloc_map(ndmaps)) != 0)
		return rc;
	initmap(number_of_blocks, ag_size, aggr_block_size);


	last_allocated = 0;

	return 0;
}
