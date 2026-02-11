solve(Input& problem, ClaspConfig& config, IncrementalControl* inc, Callback* c) {
	init(problem, config, inc, c);
	const bool onlyPre = config.enumerate.onlyPre;
	AutoState outer(this, state_start);
	LitVec assume;
	do {
		if (inc) { inc->initStep(*this); }
		result_   = result_unknown;
		more_     = true;
		if (config.ctx.master()->hasConflict() || !read() || !preprocess()) {
			result_ = result_unsat;
			more_   = false;
			reportSolution(*config.ctx.enumerator(), true);
			break;
		}
		else if (!onlyPre) {
			assume.clear();
			problem.getAssumptions(assume);
			more_    = solve(assume);
			if (result_ == result_unknown && !more_) {

				result_ = result_unsat;
			}
		}
	} while (inc && inc->nextStep(*this) && ++step_);
}
