rs_handle_result(void* vparams,
							 kdtree_t* xtree, int xnode,
							 kdtree_t* ytree, int ynode) {


	int xl, xr, yl, yr;
	int x, y;
    rs_params* p = (rs_params*)vparams;
	int D = ytree->ndim;

	xl = kdtree_left (xtree, xnode);
	xr = kdtree_right(xtree, xnode);
	yl = kdtree_left (ytree, ynode);
	yr = kdtree_right(ytree, ynode);

	for (y=yl; y<=yr; y++) {
		double py[D];
		kdtree_copy_data_double(ytree, y, 1, py);


		if (!KD_IS_LEAF(xtree, xnode)) {
			if (p->usemax &&
				kdtree_node_point_mindist2_exceeds(xtree, xnode, py,
												   p->maxdistsq))
				continue;
			if (p->usemin &&
				!kdtree_node_point_maxdist2_exceeds(xtree, xnode, py,
													p->mindistsq))
				continue;
		}
		for (x=xl; x<=xr; x++) {
			double d2;
			double px[D];
			if (p->notself && x == y)
				continue;
			kdtree_copy_data_double(xtree, x, 1, px);
			d2 = p->distsquared(px, py, D);

			if ((p->usemax) && (d2 > p->maxdistsq))
				continue;
			if ((p->usemin) && (d2 < p->mindistsq))
				continue;
			p->user_callback(p->user_callback_param, x, y, d2);
		}
	}
}
