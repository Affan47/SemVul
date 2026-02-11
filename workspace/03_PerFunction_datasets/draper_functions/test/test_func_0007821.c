simplify(const Solver& s, LitVec::size_type i) {
	for (; i < s.numAssignedVars(); ++i) {
		if (score_[s.trail()[i].var()].pos_ != vars_.end()) {
			vars_.erase(score_[s.trail()[i].var()].pos_);
			score_[s.trail()[i].var()].pos_ = vars_.end();
		}
	}
	front_ = vars_.begin();
}
