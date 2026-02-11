try_inline(node& n) {
	assert(n.subtype == NST_PSI);

	vvec &ns = n.src;

	int sz = ns.size();
	assert(sz && (sz % 3 == 0));

	value *pred_val = get_pred_val(n);

	int ps_mask = 0;

	bool r = false;

	for (int i = sz - 1; i >= 0; i -= 3) {

		if (ps_mask == 3) {
			ns.erase(ns.begin(), ns.begin() + i + 1);
			return r;
		}

		value* val = ns[i];
		value* predsel = ns[i-1];
		int ps = !predsel ? 3 : predsel == sh.get_pred_sel(0) ? 1 : 2;

		assert(val->def);

		if (val->def->subtype == NST_PSI && ps == 3) {
			if (get_pred_val(*val->def) != pred_val)
				continue;

			vvec &ds = val->def->src;

			ns.insert(ns.begin() + i + 1, ds.begin(), ds.end());
			ns.erase(ns.begin() + i - 2, ns.begin() + i + 1);
			i += ds.size();
			r = true;

		} else {
			if ((ps_mask & ps) == ps) {

				ns.erase(ns.begin() + i - 2, ns.begin() + i + 1);
			} else {
				ps_mask |= ps;
			}
		}
	}
	return r;
}
