modelHeuristic(Solver& s) {
	const bool modelHeu  = (s.strategies().optHeu & SolverStrategies::opt_model) != 0;
	const bool heuristic = modelHeu || (s.queueSize() == 0 && s.decisionLevel() == s.rootLevel());
	if (heuristic && s.propagate()) {
		for (const WeightLiteral* w = pos_; !isSentinel(w->first); ++w) {
			if (s.value(w->first.var()) == value_free) {
				s.assume(~w->first);
				if (!modelHeu || !s.propagate()) { break; }
			}
		}
	}
	return !s.hasConflict() || s.resolveConflict();
}
