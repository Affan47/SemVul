undoUntil(const Solver&, LitVec::size_type) {
	topConflict_ = topOther_ = static_cast<uint32>(-1);
	front_ = 1;
	cache_.clear();
	cacheFront_ = cache_.end();
	if (cacheSize_ > 5 && numVsids_ > 0 && (numVsids_*3) < cacheSize_) {
		cacheSize_ = static_cast<uint32>(cacheSize_/BERK_CACHE_GROW);
	}
	numVsids_ = 0;
}
