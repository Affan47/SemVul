make_ordinary(s)
char *s;
{
	int j;
	object x, l, *ep;
	vs_mark;

	set_up_string_register(s);
	j = pack_hash(string_register);
	ep = &P_EXTERNAL(lisp_package,j);
	for (l = *ep;  type_of(l) == t_cons;  l = l->c.c_cdr)
		if (string_eq(l->c.c_car, string_register))
			return(l->c.c_car);
	x = make_symbol(string_register);
	vs_push(x);
	x->s.s_hpack = lisp_package;
	*ep = make_cons(x, *ep);
	lisp_package->p.p_external_fp ++;
	vs_reset;
	return(x);
}
