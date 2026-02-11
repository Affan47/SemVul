removeConditional() {
	Literal p = ~sharedContext()->tagLiteral();
	if (!isSentinel(p)) {
		ConstraintDB::size_type i, j, end = learnts_.size();
		for (i = j = 0; i != end; ++i) {
			ClauseHead* c = static_cast<LearntConstraint*>(learnts_[i])->clause();
			if (!c || !c->tagged()) {
				learnts_[j++] = learnts_[i];
			}
			else {
				assert((decisionLevel() == rootLevel() || !c->locked(*this)) && "Solver::removeConditional(): must not remove locked constraint!");
				c->destroy(this, true);
			}
		}
		learnts_.erase(learnts_.begin()+j, learnts_.end());
	}
}
