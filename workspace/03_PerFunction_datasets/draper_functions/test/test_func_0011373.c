backtrackFromModel(Solver& s) {
	Enumerator::Result r;
	{


		Clasp::lock_guard<Clasp::mutex> lock(shared_->modelM);


		if (shared_->terminate() || !thread_[s.id()]->isModel(s)) {

			return !shared_->terminate();
		}
		r = shared_->enumerator()->backtrackFromModel(s, false);
		if (r == Enumerator::enumerate_stop_enough || (r == Enumerator::enumerate_stop_complete && s.decisionLevel() == 0)) {


			terminate(s, s.decisionLevel() == 0);
		}
		if (shared_->enumerator()->enumerated == 1 && !shared_->enumerator()->supportsRestarts()) {

			shared_->setControl(SharedData::forbid_restart_flag | SharedData::allow_gp_flag);

			thread_[s.id()]->setGpType(gp_split);
		}
	}


	if (!shared_->enumerator()->continueFromModel(s)) {
		r = Enumerator::enumerate_stop_complete;
	}
	return r == Enumerator::enumerate_continue && !shared_->terminate();
}
