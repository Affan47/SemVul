o_isobjtype(void)
{
	VALUE *vp;
	long index;

	vp = stack;
	if (vp->v_type == V_ADDR)
		vp = vp->v_addr;
	if (vp->v_type != V_STR) {
		math_error("Non-string argument for isobjtype");

	}
	index = checkobject(vp->v_str->s_str);
	freevalue(stack);
	stack->v_num = itoq(index >= 0);
	stack->v_type = V_NUM;
	stack->v_subtype = V_NOSUBTYPE;
}
