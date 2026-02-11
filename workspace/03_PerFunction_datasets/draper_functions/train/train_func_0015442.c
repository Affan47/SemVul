o_eq(void)
{
	VALUE *v1, *v2;
	int r;

	v1 = &stack[-1];
	v2 = &stack[0];
	if (v1->v_type == V_ADDR)
		v1 = v1->v_addr;
	if (v2->v_type == V_ADDR)
		v2 = v2->v_addr;
	r = comparevalue(v1, v2);
	freevalue(stack--);
	freevalue(stack);
	stack->v_num = itoq((long) (r == 0));
	stack->v_type = V_NUM;
	stack->v_subtype = V_NOSUBTYPE;
}
