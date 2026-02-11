focus_in() {
    FileBrowserImpl& fb = *impl_;
    if (fb.selected_ == -1) {
	fb.select_top();
    } else {
	Browser::select(fb.selected_);
    }
    return Browser::focus_in();
}
