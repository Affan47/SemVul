reportProgress(const SolveEvent& e) {
	if (e.type != SolveEvent_t::progress_path || static_cast<const SolvePathEvent&>(e).evType != SolvePathEvent::event_restart) { return; }
	const SolvePathEvent& ev = static_cast<const SolvePathEvent&>(e);
	std::stringstream temp;
	const Solver& s = *ev.solver;
	uint64 maxC     = ev.cLimit;
	uint32 maxL     = ev.lLimit;
	if (format_ == Options::features_verbose) {
		printf("\n[Iteration %u]\n", starts_);
		printf("%-22s: %u\n", "maxLearnt", maxL);
		printf("%-22s: %" PRIu64"\n", "maxConflicts", maxC);
		printf("%-22s: %u\n", "Constraints", s.numConstraints());
		printf("%-22s: %u\n", "LearntConstraints", s.numLearntConstraints());
		printf("%-22s: %u\n", "FreeVars", s.numFreeVars());
		printf("%-22s: %.3f\n", "Vars/FreeVars", ((double)s.numVars())/std::max(s.numFreeVars(),uint32(1)));
		printf("%-22s: %.3f\n", "FreeVars/Constraints", ((double)s.numFreeVars())/s.numConstraints());
		printf("%-22s: %.3f\n", "Vars/Constraints", ((double)s.numVars())/s.numConstraints());
		printf("%-22s: %.3f\n", "maxLearnt/Constraints", ((double)maxL)/s.numConstraints());
		if (s.stats.jumps) {
			printf("%-22s: %.3f\n", "Average Jump Length", average(s.stats.jumps->jumpSum, s.stats.analyzed));
		}
		printf("=================================\n\n");
	}
	else {
		uint32 numC = std::max(s.numConstraints(), uint32(1));
		temp.precision(3);
		temp << std::fixed << maxL << "," << maxC << "," << s.numConstraints() << "," << s.numLearntConstraints() << "," << s.numFreeVars() << ","
			   << (static_cast<double>(s.numVars())/std::max(s.numFreeVars(), uint32(1))) << ","
				 << (static_cast<double>(s.numFreeVars())/numC) << ","
				 << (static_cast<double>(s.numVars())/numC) << ","
				 << (static_cast<double>(maxL)/numC);
		if (format_ == Options::features_compact_1) {
			printf("%s\n", temp.str().c_str());
		}
		else {
			if (!iterationBuffer_.empty()) iterationBuffer_ += ",";
			iterationBuffer_ += temp.str();
		}
	}
	++starts_;
}
