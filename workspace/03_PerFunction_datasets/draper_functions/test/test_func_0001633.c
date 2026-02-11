o_isreal(void)
{
	VALUE *vp;

	vp = stack;
	if (vp->v_type == V_ADDR)
		vp = vp->v_addr;
	if (vp->v_type == V_NUM) {
		if (stack->v_type == V_NUM)
			qfree(stack->v_num);
		stack->v_num = qlink(&_qone_);
		stack->v_type = V_NUM;
		stack->v_subtype = V_NOSUBTYPE;
		return;
	}
	freevalue(stack);
	stack->v_num = qlink(&_qzero_);
	stack->v_type = V_NUM;
	stack->v_subtype = V_NOSUBTYPE;
}
