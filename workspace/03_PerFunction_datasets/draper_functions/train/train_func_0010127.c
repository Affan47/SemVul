clear() {
	score.clearDeps();
	while (!saved_.empty()) {
		if (saved_.back() != UINT32_MAX) {
			splice(saved_.back());
		}
		saved_.pop_back();
	}
	LookList(2, *head()).swap(nodes_);
	head()->next = head_id;
	undo()->next = UINT32_MAX;
	last_        = head_id;
	top_         = UINT32_MAX;
}
