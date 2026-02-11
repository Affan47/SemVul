Up() {
    if (state_->Active()) {
	Control* target = state_->Selection();
	state_->Action(target);
	for (ControlState* c = state_; c != nil; c = c->Prev()) {
	    c->Deactivate();
	}
	if (target != nil) {
	    Busy();
	    target->Do();
	    Done();
	}
    }
}
