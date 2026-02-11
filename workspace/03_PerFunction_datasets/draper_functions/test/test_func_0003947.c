process_defs(node *n, vvec &vv, bool arr_def) {

	for (vvec::iterator I = vv.begin(), E = vv.end(); I != E; ++I) {
		value *v = *I;
		if (!v)
			continue;

		if (arr_def)
			v->adef = n;
		else
			v->def = n;

		v->delete_uses();

		if (v->is_rel()) {
			process_defs(n, v->mdef, true);
		}
	}
}
