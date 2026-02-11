isTrue(const Solver& s, uint32 idx) {
	if (idx != end_-1) return s.isTrue(lits_[idx]);
	for (uint32 x = end_+1; x != size_; ++x) {
		if (!s.isTrue(lits_[x])) {
			lits_[end_-1] = lits_[x];
			return false;
		}
	}
	return true;
}
