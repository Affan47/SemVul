init(const Solver& s) {
	if (s.strategies().heuReinit) { score.clear(); }
	score.resize(s.numVars()+1);
}
