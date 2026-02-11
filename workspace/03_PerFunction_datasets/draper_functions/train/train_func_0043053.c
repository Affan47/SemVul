ccMinimize(LitVec& cc, LitVec& removed, uint32 antes, CCMinRecursive* ccMin) {
	if (ccMin) { ccMin->init(numVars()+1); }

	LitVec::size_type j = 1;
	uint32 assertLevel  = 0;
	uint32 assertPos    = 1;
	uint32 onAssert     = 0;
	uint32 varLevel     = 0;
	for (LitVec::size_type i = 1; i != cc.size(); ++i) {
		if (antes == 0 || !ccRemovable(~cc[i], antes-1, ccMin)) {
			if ( (varLevel = level(cc[i].var())) > assertLevel ) {
				assertLevel = varLevel;
				assertPos   = static_cast<uint32>(j);
				onAssert    = 0;
			}
			onAssert += (varLevel == assertLevel);
			cc[j++] = cc[i];
		}
		else {
			removed.push_back(cc[i]);
		}
	}
	cc.erase(cc.begin()+j, cc.end());
	if (assertPos != 1) {
		std::swap(cc[1], cc[assertPos]);
	}
	if (ccMin) { ccMin->clear(); }
	return onAssert;
}
