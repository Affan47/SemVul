arithmetic_common(VALUE *l, VALUE *r, int op)
{
	arith_t li, ri;

	if (!toarith(l) || !toarith(r))
		bb_error_msg_and_die("non-numeric argument");
	li = l->u.i;
	ri = r->u.i;
	if (op == '+')
		return li + ri;
	if (op == '-')
		return li - ri;
	if (op == '*')
		return li * ri;
	if (ri == 0)
		bb_error_msg_and_die("division by zero");
	if (op == '/')
		return li / ri;
	return li % ri;
}
