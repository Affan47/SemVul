keystroke(const Event& e) {
    char c;
    if (e.mapkey(&c, 1) != 0) {
	FileBrowserImpl& fb = *impl_;
	FileBrowserKeyFunc f = fb.key_[c];
	if (f != nil) {
	    (fb.*f)();
	}
    }
}
