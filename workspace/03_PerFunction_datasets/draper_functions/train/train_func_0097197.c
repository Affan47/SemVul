try_match(nil *t, term *r, match *m) {
	if(r->type == TNIL) {
		m->add_match(r,t);
		m->success();
		return match::singleton(m);
	} else if (r->type == THOLE) {
		m->success();
		m->add_param(((hole *)r)->index, t);
		return match::singleton(m);
	}

	return m->failure();
}
