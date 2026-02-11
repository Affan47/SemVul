visit(not_expr& x)  {

		iter_match(x.e, *changed, *visited);

		match = gen_set{1};
	}
