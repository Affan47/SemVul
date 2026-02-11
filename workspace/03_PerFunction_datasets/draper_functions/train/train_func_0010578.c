get_dyna_var_idx(rb_iseq_t *iseq, ID id, int *level, int *ls)
{
    int lv = 0, idx = -1;

    while (iseq) {
	idx = get_dyna_var_idx_at_raw(iseq, id);
	if (idx >= 0) {
	    break;
	}
	iseq = iseq->parent_iseq;
	lv++;
    }

    if (idx < 0) {
	rb_bug("get_dyna_var_idx: -1");
    }

    *level = lv;
    *ls = iseq->local_size;
    return idx;
}
