momsScore(const Solver& s, Var v) {
	uint32 sc;
	if (s.sharedContext()->numBinary()) {
		uint32 s1 = s.estimateBCP(posLit(v), 0) - 1;
		uint32 s2 = s.estimateBCP(negLit(v), 0) - 1;
		sc = ((s1 * s2)<<10) + (s1 + s2);
	}
	else {

		uint32 s1 = s.numWatches(posLit(v));
		uint32 s2 = s.numWatches(negLit(v));
		sc = ((s1 * s2)<<10) + (s1 + s2);
	}
	return sc;
}
