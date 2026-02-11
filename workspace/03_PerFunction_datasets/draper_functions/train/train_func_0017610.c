add_vec(vvec &vv, bool src) {
	bool r = false;
	for (vvec::iterator I = vv.begin(), E = vv.end(); I != E; ++I) {
		value *v = *I;
		if (!v || v->is_readonly())
			continue;

		if (v->is_rel()) {
			r |= add_vec(v->muse, true);
			if (v->rel->is_any_reg())
				r |= live.add_val(v->rel);

		} else if (src) {
			r |= live.add_val(v);
		}
	}

	return r;
}
