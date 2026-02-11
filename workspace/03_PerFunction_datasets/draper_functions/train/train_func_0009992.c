update(Solver& s, bool disjoint) {
	EnumeratorConstraint* c = constraint(s);
	uint32 gUpdates;
	if (!c || c->updates() == (gUpdates = updates_)) {
		return true;
	}
	bool ret   = true;
	if (optimize()) {
		ret      = c->minimize()->integrateNext(s);
		disjoint = true;
	}
	if (ret && (ret = updateConstraint(s, disjoint)) == true) {
		c->setUpdates(gUpdates);
	}
	return ret;
}
