analyse(reactionrule *r) {
	controlvisitor *c1 = new controlvisitor();
	controlvisitor *c2 = new controlvisitor();

	r->redex->accept(c1);
	r->reactum->accept(c2);


	ruleattr *a = new ruleattr();

	a->rule = r;

	delta_t sd;
	sd.delta = c2->size - c1->size;

	delta_t dd;
	dd.delta = c2->depth - c1->depth;


	if(c1->nholes == c2->nholes) {
		sd.valid = true;
		dd.valid = true;
	} else if (c2->nholes < c1->nholes) {
		sd.valid = true;
		dd.valid = true;
	} else {
		sd.valid = false;
		dd.valid = false;
	}

	a->size_delta = sd;
	a->depth_delta = dd;

	a->precond = c1->controls;
	a->postcond = c2->controls;

	delete c1;
	delete c2;

	return a;
}
