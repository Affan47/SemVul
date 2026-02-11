Notify() {
    int v;
    GetValue(v);
    value = 0;
    if (action_ != nil) {
	switch (v) {
	case '\r':
	    action_->accept(editor_);
	    break;
	case  '\007':
	case  '\033':
	    action_->cancel(editor_);
	    break;
	default:
	    break;
	}
    }
}
