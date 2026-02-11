frame_func_id(rb_control_frame_t *cfp)
{
    const rb_method_entry_t *me_local;
    rb_iseq_t *iseq = cfp->iseq;
    if (cfp->me) {
	return cfp->me->def->original_id;
    }
    while (iseq) {
	if (RUBY_VM_IFUNC_P(iseq)) {
	    NODE *ifunc = (NODE *)iseq;
	    if (ifunc->nd_aid) return ifunc->nd_aid;
	    return rb_intern("<ifunc>");
	}
	me_local = method_entry_of_iseq(cfp, iseq);
	if (me_local) {
	    cfp->me = me_local;
	    return me_local->def->original_id;
	}
	if (iseq->defined_method_id) {
	    return iseq->defined_method_id;
	}
	if (iseq->local_iseq == iseq) {
	    break;
	}
	iseq = iseq->parent_iseq;
    }
    return 0;
}
