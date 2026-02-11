execute() {
    if (state_->test(TelltaleState::is_chosen)) {
	if (!placed_) {
	    pinned_->place(unpinned_->left(), unpinned_->bottom());
	    pinned_->align(0.0, 0.0);
	    placed_ = true;
	}
	pinned_->map();
    } else {
	pinned_->unmap();
    }
}
