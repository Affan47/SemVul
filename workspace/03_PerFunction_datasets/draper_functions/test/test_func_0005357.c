action(Action* a) {
    if (a != action_) {
	Resource::ref(a);
	Resource::unref(action_);
	action_ = a;
    }
}
