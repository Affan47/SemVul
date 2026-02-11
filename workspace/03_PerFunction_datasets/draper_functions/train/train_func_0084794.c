rb_proc_arity(VALUE self)
{
    rb_proc_t *proc;
    rb_iseq_t *iseq;
    GetProcPtr(self, proc);
    iseq = proc->block.iseq;
    if (iseq) {
	if (BUILTIN_TYPE(iseq) != T_NODE) {
	    if (iseq->arg_rest < 0) {
		return iseq->argc;
	    }
	    else {
		return -(iseq->argc + 1 + iseq->arg_post_len);
	    }
	}
	else {
	    NODE *node = (NODE *)iseq;
	    if (IS_METHOD_PROC_NODE(node)) {

		return method_arity(node->nd_tval);
	    }
	}
    }
    return -1;
}
