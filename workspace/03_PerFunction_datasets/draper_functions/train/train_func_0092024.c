wait() {
		Clasp::unique_lock<Clasp::mutex> lock(semMutex_);
		if (--counter_ >= 0) { counter_ = -1; }
		return unsafe_wait(lock);
	}
