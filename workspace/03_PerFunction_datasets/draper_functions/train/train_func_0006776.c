gcMalloc(size_t size){
	void* ptr = malloc(size);


	if(!addNewPtr(global.gc, ptr)){
		return NULL;
	}


	return ptr;
}
