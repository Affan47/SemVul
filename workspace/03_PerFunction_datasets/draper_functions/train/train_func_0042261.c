setGraph() {
	if (!graph_.get() && api_->dependencyGraph() && api_->dependencyGraph()->nodes() > 0) {
		graph_ = api_->dependencyGraph(true);
		for (uint32 i = 0; i != config_->numSolvers(); ++i) {
			DefaultUnfoundedCheck* ufs = new DefaultUnfoundedCheck();
			ufs->attachTo(*config_->getSolver(i)->solver, graph_.get());
		}
	}
}
