DeleteResultStack() {
	DcmDataset* obj = NULL;
	unsigned int size = result.card();

	for(Uint32 i=0; i < size; i++){
		obj = (DcmDataset*)result.elem(i);
		delete obj;
	}

	result.clear();
}
