start_parent_slice_with_credit(struct throtl_grp *child_tg,
					struct throtl_grp *parent_tg, bool rw)
{
	if (throtl_slice_used(parent_tg, rw)) {
		throtl_start_new_slice_with_credit(parent_tg, rw,
				child_tg->slice_start[rw]);
	}

}
