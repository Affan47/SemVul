src_commit_write(struct src *src)
{
	struct hw *hw;
	int i;
	unsigned int dirty = 0;

	hw = src->rsc.hw;
	src->rsc.ops->master(&src->rsc);
	if (src->rsc.msr > 1) {

		dirty = hw->src_get_dirty(src->rsc.ctrl_blk) & conj_mask;
	}
	hw->src_commit_write(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);


	if (MEMWR == src->mode)
		return 0;

	for (i = 1; i < src->rsc.msr; i++) {
		src->rsc.ops->next_conj(&src->rsc);
		hw->src_set_dirty(src->rsc.ctrl_blk, dirty);
		hw->src_commit_write(hw, src->rsc.ops->index(&src->rsc),
							src->rsc.ctrl_blk);
	}
	src->rsc.ops->master(&src->rsc);

	return 0;
}
