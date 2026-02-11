initialize_new_portion(struct gfs2_sbd *sdp, int *old_rg_count)
{
	struct osi_node *n, *next = NULL;
	uint64_t rgrp = 0;
	struct rgrp_tree *rl;

	*old_rg_count = 0;

	for (rgrp = 0, n = osi_first(&sdp->rgtree);
	     n && rgrp < (sdp->rgrps - sdp->new_rgrps); n = next, rgrp++) {
		next = osi_next(n);
		(*old_rg_count)++;
		rl = (struct rgrp_tree *)n;
		osi_erase(&rl->node, &sdp->rgtree);
		free(rl);
	}

	rl = (struct rgrp_tree *)n;
	discard_blocks(sdp->device_fd, rl->start * sdp->bsize,
		       (sdp->device.length - rl->start) * sdp->bsize);

	build_rgrps(sdp, !test);

	inode_put(&sdp->md.riinode);
	inode_put(&sdp->master_dir);


	fsync(sdp->device_fd);
}
