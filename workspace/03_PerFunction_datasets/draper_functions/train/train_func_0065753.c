filesystem_size(struct gfs2_sbd *sdp)
{
	struct osi_node *n, *next = NULL;
	struct rgrp_tree *rgl;
	uint64_t size = 0, extent;

	for (n = osi_first(&sdp->rgtree); n; n = next) {
		next = osi_next(n);
		rgl = (struct rgrp_tree *)n;
		extent = rgl->ri.ri_addr + rgl->ri.ri_length + rgl->ri.ri_data;
		if (extent > size)
			size = extent;
	}
	return size;
}
