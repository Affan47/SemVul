undoLevel(Solver&) {
	assert(undoTop_ != 0 && posTop_ > undoTop_);
	uint32 up  = undoTop_;
	uint32 idx = undo_[--posTop_].index();
	for (;;) {
		UndoInfo& u = undo_[--up];
		undo_[u.index()].data.idxSeen = 0;
		STRATEGY(subtract(sum_, shared_->lits[u.index()].second));
		if (u.newDL()) {
			break;
		}
	}
	undoTop_ = up;
	Iter temp= shared_->lits + idx;
	if (temp < pos_) pos_ = temp;
}
