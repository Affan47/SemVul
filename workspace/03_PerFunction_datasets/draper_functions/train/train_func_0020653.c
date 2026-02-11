rename_package(x, n, ns)
object x, n, ns;
{

	object y;
	vs_mark;

	if (type_of(n) == t_symbol) {
		vs_push(alloc_simple_string(n->s.s_fillp));
		vs_head->st.st_self = n->s.s_self;
		n = vs_head;
	}
	if (type_of(n)==t_character)
	  n=coerce_to_string(n);
   	if (!(equal(x->p.p_name,n)) &&
	    find_package(n) != Cnil)
		package_already(n);
	x->p.p_name = n;
	x->p.p_nicknames = Cnil;
	for (;  !endp(ns);  ns = ns->c.c_cdr) {
		n = ns->c.c_car;
		if (type_of(n) == t_symbol) {
			vs_push(alloc_simple_string(n->s.s_fillp));
			vs_head->st.st_self = n->s.s_self;
			n = vs_head;
		}
		if (type_of(n)==t_character)
		  n=coerce_to_string(n);
		y = find_package(n);
		if (x == y)
			continue;
		if (y != Cnil)
			package_already(n);
		x->p.p_nicknames = make_cons(n, x->p.p_nicknames);
	}
	vs_reset;
	return(x);
}
