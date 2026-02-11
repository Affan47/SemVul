make(memo_expr::table& memo, ptr<expr> a, ptr<expr> b) {
		switch ( a->type() ) {

		case fail_type: return b;

		case inf_type:  return a;
		default:        break;
		}


		if ( b->type() == fail_type || ! a->match().empty() ) return a;

		bool did_inc = false;
		gen_map ag = expr::default_back_map(a, did_inc);
		gen_map bg = expr::default_back_map(b, did_inc);
		return expr::make_ptr<alt_expr>(memo, a, b, ag, bg, 0 + did_inc);
	}
