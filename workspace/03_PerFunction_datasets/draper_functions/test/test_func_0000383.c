Redraw(bool update) {
	PG_Rect r(0, 0, my_width, my_height);

	if(my_srfObject != NULL) {
		eventDraw(my_srfObject, r);
	}

	if(_mid->childList != NULL) {
		for(PG_Widget* i = _mid->childList->first(); i != NULL; i = i->next()) {
			i->Redraw(false);
		}
	}

	if (update) {
		Update();
	}
	return true;
}
