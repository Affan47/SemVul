simplifyBodies(Var atomId, ProgramBuilder& prg, bool strong) {
	HeadVec::iterator j = preds.begin();
	Var eq;
	uint32 diffLits = 0;
	for (HeadVec::iterator it = preds.begin(), end = preds.end(); it != end; ++it) {
		if ( (eq = prg.getEqBody(it->node())) != it->node() ) { *it = HeadEdge(eq, it->type()); }
		PrgBodyNode* x = prg.bodies_[it->node()];
		if (!x->ignore() && x->value() != value_false && (!strong || x->hasHead(atomId))) {
			if (!it->normal()) {
				for (HeadVec::iterator k = it; ++k != end; ) {
					if ( (eq = prg.getEqBody(k->node())) != k->node() ) { *k = HeadEdge(eq, k->type()); }
					if (k->node() == it->node() && k->type() < it->type()) {
						*it = *k;
					}
				}
			}
			*j++ = *it;
			if (strong && (!prg.vars_.marked(x->literal()) || !it->normal())) {
				++diffLits;
				if (it->normal()) { prg.vars_.mark(x->literal()); }
			}
			x->setIgnore(true);
		}
	}
	preds.erase(j, preds.end());
	for (HeadVec::iterator it = preds.begin(), end = preds.end(); it != end; ++it) {
		prg.bodies_[it->node()]->setIgnore(false);
		if (strong) { prg.vars_.unmark(prg.bodies_[it->node()]->var()); }
	}
	if (!strong) diffLits = (uint32)preds.size();
	if (preds.empty()) {
		setIgnore(true);
		return SimpRes(setValue(value_false), 0);
	}
	return SimpRes(true, diffLits);
}
