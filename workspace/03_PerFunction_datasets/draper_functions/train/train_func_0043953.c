undoLevel(Solver& s) {
	setBpIndex(1);
	for (UndoInfo u; up_ != undoStart() && s.value(lits_->var((u=undoTop()).idx())) == value_free;) {
		assert(litSeen(u.idx()));
		toggleLitSeen(u.idx());
		bound_[u.constraint()] += weight(u.idx());
		--up_;
	}
	if (!litSeen(0)) active_ = NOT_ACTIVE;
}
