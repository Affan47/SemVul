operator()(tick *t) {
	shiftcpy sc(&t->shift);
	t->side = side;
	t->size = size;

	for_each(shift.begin(), shift.end(), sc);

	the_graph->base->tks.push_back(t);
	if ( t->side == top_side || t->side == bottom_side )
	    t->c->newx(t->where);
	else
	    t->c->newy(t->where);
	return 0;
    }
}
