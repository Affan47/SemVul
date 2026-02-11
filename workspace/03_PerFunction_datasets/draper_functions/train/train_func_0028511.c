create(size_t width, size_t height, const char* shared_id) {
	if(__SHARED_MATRIX_DISABLED) shared_id = NULL;

	if(shared_id) {
		bShared = true;
		if(attach(shared_id)) {
			if(this->width==width && this->height==height) 	return;
			cout << "But matrix dimensions does not agree : reshaping ... ok\n";
			delete_shared();
		}
		key = create_key(id);
		try {
			size_t* _data = (size_t*)create_shared_mem(key, width*height*sizeof(float) + 2*sizeof(size_t), &_shmid);
			*_data++ = width;
			*_data++ = height;
			data = (float*)_data;

		} catch(...) {
			data = 0;
			cerr << "Couldn't allocate shared matrix " << shared_id << "\n";
			unlink(id.c_str());
			throw "Couldn't allocate shared matrix";
		}
	} else {
		bShared = false;
		data = new float[width*height];

	}

	this->width = width; this->height = height;
}
