o_mul(void)
{
	VALUE *v1, *v2;
	VALUE tmp;
	VALUE w1, w2;

	v1 = &stack[-1];
	v2 = &stack[0];
	if (v1->v_type == V_ADDR)
		v1 = v1->v_addr;
	if (v2->v_type == V_ADDR)
		v2 = v2->v_addr;
	if (v1->v_type == V_OCTET) {
		w1.v_type = V_NUM;
		w1.v_subtype = V_NOSUBTYPE;
		w1.v_num = itoq(*v1->v_octet);
		v1 = &w1;
	}
	if (v2->v_type == V_OCTET) {
		w2.v_type = V_NUM;
		w2.v_subtype = V_NOSUBTYPE;
		w2.v_num = itoq(*v2->v_octet);
		v2 = &w2;
	}
	mulvalue(v1, v2, &tmp);
	if (v1 == &w1)
		qfree(w1.v_num);
	if (v2 == &w2)
		qfree(w2.v_num);
	freevalue(stack--);
	freevalue(stack);
	*stack = tmp;
}
