reduceLearnts(float remFrac, const ReduceStrategy& rs) {
	uint32 oldS = numLearntConstraints();
	uint32 remM = static_cast<uint32>(oldS * std::max(0.0f, remFrac));
	DBInfo r    = {0,0,0};
	CmpScore cmp(learnts_, (ReduceStrategy::Score)rs.score, rs.glue);
	if (remM >= oldS || !remM || rs.algo == ReduceStrategy::reduce_sort) {
		r = reduceSortInPlace(remM, cmp, false);
	}
	else if (rs.algo == ReduceStrategy::reduce_stable) { r = reduceSort(remM, cmp);  }
	else if (rs.algo == ReduceStrategy::reduce_heap)   { r = reduceSortInPlace(remM, cmp, true);}
	else                                               { r = reduceLinear(remM, cmp); }
	stats.addDeleted(oldS - r.size);
	shrinkVecTo(learnts_, r.size);
	return r;
}
