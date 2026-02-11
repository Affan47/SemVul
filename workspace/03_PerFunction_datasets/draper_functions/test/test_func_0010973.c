o_numerator(void)
{
	VALUE *vp;
	NUMBER *q;

	vp = stack;
	if (vp->v_type == V_ADDR)
		vp = vp->v_addr;
	if (vp->v_type != V_NUM) {
		math_error("Numerator of non-number");

	}
	if ((stack->v_type == V_NUM) && qisint(vp->v_num))
		return;
	q = qnum(vp->v_num);
	if (stack->v_type == V_NUM)
		qfree(stack->v_num);
	stack->v_num = q;
	stack->v_type = V_NUM;
	stack->v_subtype = V_NOSUBTYPE;
}
