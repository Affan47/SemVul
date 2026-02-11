minimize(Solver& s, Literal p, CCMinRecursive* rec) {
	assert(active_ != NOT_ACTIVE);
	Literal x;
	uint32 stop = !isWeight() ? up_ : s.reasonData(p);
	assert(stop <= up_);
	for (uint32 i = undoStart(); i != stop; ++i) {
		UndoInfo u = undo_[i];

		if (u.constraint() == (ActiveConstraint)active_) {
			x = lit(u.idx(), u.constraint());
			if (!s.ccMinimize(~x, rec)) {
				return false;
			}
		}
	}
	return true;
}
