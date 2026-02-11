initSolve(const Solver& s, ProgramBuilder* api) {
	DefaultOutput::initSolve(s, api);
	starts_          = 0;
	iterationBuffer_ = "";
	if (format_ != Options::features_verbose) {
		int v = (format_ == Options::features_compact_3);
		setVerbosity(v);
	}
}
