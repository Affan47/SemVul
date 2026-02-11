simplify(RuleState& rs) {
	RData r = { 0, 0, 0, 0 };
	if (!(bodyIsSet()?simplifyNormal(r,rs):simplifyWeight(r,rs))) {
		type_    = ENDRULE;
		r.value  = value_false;
		return r;
	}
	else if (type_ != OPTIMIZERULE && bound() <= 0) {
		r.value = value_true;
	}
	Weights w(*this);

	if (type_ != ENDRULE) {
		VarVec::iterator j = heads.begin();
		for (VarVec::iterator it = heads.begin(), end = heads.end();  it != end; ++it) {
			if ( !rs.inHead(*it) && !rs.superfluousHead(type()==CHOICERULE, r.sumWeight, bound(), *it, w)) {
				rs.addToHead(*it);
				if (rs.selfblocker(type()==CHOICERULE, r.sumWeight, bound(), *it, w)) {
					r.value = value_false;
				}
				*j++ = *it;
			}
		}
		heads.erase(j, heads.end());
		if (heads.empty() && type_ != OPTIMIZERULE) type_ = ENDRULE;
	}
	return r;
}
