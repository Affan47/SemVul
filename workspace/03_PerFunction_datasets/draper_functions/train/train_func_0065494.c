convert(const Optimum* opt, bool applyStep, wsum_t* optOut) const {
	wsum_t n    = opt->step.second;
	applyStep  &= (n != 0);
	uint32 i    = static_cast<uint32>(opt->opt.size());
	uint32 lev  = applyStep ? opt->step.first : i;
	bool   ap   = !applyStep;
	for (wsum_t t; i--; ) {
		t         = opt->opt[i];
		if (i > lev) {
			t       = std::numeric_limits<wsum_t>::max();
		}
		else if (!ap && lev != UINT32_MAX) {
			t       = opt->opt[i] - n;
			if (t  >= sum_[i]) { ap = true; }
			else               { t  = std::numeric_limits<wsum_t>::max(); }
		}
		optOut[i] = t;
	}
	return ap;
}
