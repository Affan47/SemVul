integrate(Solver& s, SharedLiterals* clause) {
	if (!clause) return true;
	ClauseCreator::Result ret(0, ClauseCreator::status_conflicting);
	if (clause->size() > 0) {
		ret = ClauseCreator::integrate(s, clause, ClauseCreator::clause_explicit|ClauseCreator::clause_no_add);
		if (ret.local) { add(s, ret.local); }
	}
	else {
		s.setStopConflict();
	}
	return ret.ok();
}
