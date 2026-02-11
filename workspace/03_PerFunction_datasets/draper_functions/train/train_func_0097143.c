Add(PG_Widget* rect, bool front) {
	if(rect->next() != NULL || rect->prev() != NULL) {
		PG_LogWRN("PG_RectList::Add(...) Trying to add a linked PG_Rect object");
		return;
	}

	Uint32 index = 2^31;
	my_count++;


	if(my_last != NULL) {
		index = my_last->index;
	}
	index++;

	if(front) {
		if(my_first != NULL) {
			my_first->my_prev = rect;
			rect->index = my_first->index-1;
		} else {
			rect->index = index;
		}
		rect->my_next = my_first;
		rect->my_prev = NULL;
		my_first = rect;
		return;
	}

	if(my_first == NULL) {
		my_first = rect;
		rect->my_prev = NULL;
		rect->my_next = NULL;
	} else {
		my_last->my_next = rect;
		rect->my_next = NULL;
		rect->my_prev = my_last;
	}
	my_last = rect;
	rect->index = index;
}
