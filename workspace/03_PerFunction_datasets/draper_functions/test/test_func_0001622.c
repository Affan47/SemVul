initSolve(const Solver& s, ProgramBuilder* api) {

	if (api) {
		if (!lpStats_) lpStats_ = new PreproStats;
		lpStats_->accu(api->stats);
	}
	saved_.resize(2*s.assignment().numVars());
	curr_ = 0;
	next_ = &saved_[0];
}
