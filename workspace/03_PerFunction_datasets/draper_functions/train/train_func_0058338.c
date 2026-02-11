clearDB(Solver* s) {
	for (ClauseDB::iterator it = integrated_.begin(), end = integrated_.end(); it != end; ++it) {
		ClauseHead* c = static_cast<ClauseHead*>(*it);
		if (s && c->locked(*s)) { s->addLearnt(c, c->size(), Constraint_t::learnt_other); }
		else                    { c->destroy(s, s != 0); }
	}
	integrated_.clear();
	intTail_= 0;
}
