remove_input_handler(GlyphIndex index) {
    InputHandlerImpl& i = *impl_;
    InputHandlerList& list = i.children_;
    if (list.item(index) == i.focus_handler_) {
	next_focus();
	if (list.item(index) == i.focus_handler_) {
	    i.focus_handler_ = nil;
	}
    }
    list.remove(index);
}
