add( ITEM* newItem ) {
	C_Element* newE = new C_Element();
	if(newE == NULL) { return false; };

	newE->item = newItem;
	newE->previous = this->last;
	newE->next = NULL;

	if(this->last != NULL) {
		this->last->next = newE;
	} else {
		this->first = newE;
	}
	this->last = newE;

	return true;
}
