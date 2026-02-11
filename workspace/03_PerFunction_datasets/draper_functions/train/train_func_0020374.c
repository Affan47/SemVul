o_xor (void)
{
	VALUE *v1, *v2;
	VALUE tmp;

	v1 = &stack[-1];
	v2 = &stack[0];

	if (v1->v_type == V_ADDR)
		v1 = v1->v_addr;
	if (v2->v_type == V_ADDR)
		v2 = v2->v_addr;

	xorvalue(v1, v2, &tmp);
	freevalue(stack--);
	freevalue(stack);
	*stack = tmp;
}
