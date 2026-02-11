gcFreeAll(){
	struct gcItem* item = global.gc->list;

	int i = 0;
	while(item != NULL){

		global.gc->list = item->next;


		free(item->ptr);
		free(item);


		global.gc->listLength--;
		i++;

		item = global.gc->list;
	}

	if(global.gc->listLength == 0)
		Log("free_all:\tall free done", DEBUG, GC);
	else
		Log("free_add:\tmemory leak", DEBUG, GC);
}
