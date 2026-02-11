estimateComplexity(const Solver& s) const {
	weight_t w1 = bound_[0];
	weight_t w2 = bound_[1];
	uint32 r    = 2;
	for (uint32 i = 1; i != size(); ++i) {
		if (s.value(lits_->var(i)) == value_free) {
			++r;
			if ( (w1 -= weight(i)) <= 0 ) break;
			if ( (w2 -= weight(i)) <= 0 ) break;
		}
	}
	return r;
}
}
