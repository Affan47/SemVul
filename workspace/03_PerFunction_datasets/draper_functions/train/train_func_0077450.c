Detach(Interactor* i) {
    register ViewList* e;
    register ViewList* prev;

    prev = nil;
    for (e = views; e != nil; e = e->next) {
	if (e->view == i) {
	    if (prev == nil) {
		views = e->next;
	    } else {
		prev->next = e->next;
	    }
	    e->view = nil;
	    e->next = nil;
	    delete e;
	    Unreference();
	    break;
	}
	prev = e;
    }
}
