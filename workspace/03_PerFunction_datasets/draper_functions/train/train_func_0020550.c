zSFListGetCurrent(zSFList* l){
	if((l->current == l->head) ||
	   (l->current == l->tail)){
		return NULL;
	}
	else{
		return &l->current->data;
	}
}
