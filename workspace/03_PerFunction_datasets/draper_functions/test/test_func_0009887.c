kwote_cdr(void)
{
	object x;

	x = vs_head;
	if (type_of(x) == t_symbol) {
		if ((enum stype)x->s.s_stype == stp_constant &&
		    x->s.s_dbind == x)
			return;
		goto KWOTE;
	} else if (type_of(x) == t_cons || type_of(x) == t_vector)
		goto KWOTE;
	return;

KWOTE:
	vs_head = make_cons(vs_head, Cnil);
	vs_head = make_cons(sLquote, vs_head);
}
