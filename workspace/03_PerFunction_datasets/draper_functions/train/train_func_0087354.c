minimize(Solver& s, Literal p, CCMinRecursive* rec) {
	ClauseHead::bumpActivity();
	uint32 other = p == head_[0];
	if (!s.ccMinimize(~head_[other], rec) || !s.ccMinimize(~head_[2], rec)) { return false; }
	LitRange t = tail();
	for (const Literal* r = t.first; r != t.second; ++r) {
		if (!s.ccMinimize(~*r, rec)) { return false; }
	}
	if (contracted()) {
		do {
			if (!s.ccMinimize(~*t.second, rec)) { return false; }
		} while (!t.second++->watched());
	}
	return true;
}
