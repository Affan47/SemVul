o_ishash(void)
{
	VALUE *vp;
	int r;

	vp = stack;
	if (vp->v_type == V_ADDR)
		vp = vp->v_addr;
	r = (vp->v_type == V_HASH);
	if (r != 0)
		r = vp->v_hash->hashtype;
	freevalue(stack);
	stack->v_num = itoq((long) r);
	stack->v_type = V_NUM;
	stack->v_subtype = V_NOSUBTYPE;
}
