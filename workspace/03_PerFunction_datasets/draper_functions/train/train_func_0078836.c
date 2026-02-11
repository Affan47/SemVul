handleMessages(Solver& s) {

	if (!shared_->hasMessage()) {

		return true;
	}
	uint32 hId         = s.id();
	ParallelHandler* h = thread_[hId];
	if (shared_->terminate()) {
		reportProgress(SolveMsgEvent(s, "TERMINATE message received"));
		h->handleTerminateMessage();
		s.setStopConflict();
		return false;
	}
	if (shared_->synchronize()) {
		if (waitOnSync(s)) {
			s.setStopConflict();
			return false;
		}
		return true;
	}
	if (h->disjointPath() && s.splittable() && shared_->workReq > 0) {


		shared_->aboutToSplit();
		h->handleSplitMessage();
	}
	return true;
}
