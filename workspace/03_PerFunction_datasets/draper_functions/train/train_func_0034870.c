cloneAttach(Clasp::Solver &o) {
	NullConstraint* c = new NullConstraint();
	return c->attach(o), c;
}
