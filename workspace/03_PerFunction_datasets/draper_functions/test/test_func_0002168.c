o_ptr(void)
{
	switch (stack->v_type) {
	case V_ADDR:
		stack->v_type = V_VPTR;
		break;
	case V_OCTET:
		stack->v_type = V_OPTR;
		break;
	case V_STR:
		sfree(stack->v_str);
		stack->v_type = V_SPTR;
		break;
	case V_NUM:
		qfree(stack->v_num);
		stack->v_type = V_NPTR;
		break;
	default:
		math_error("Addressing non-addressable type");

	}
}
