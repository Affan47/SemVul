bt_vector_add_ptr(torrent_vect* vect, void* item)
{

	if (vect->size >= vect->allocated) {
		size_t size = (vect->allocated == 0 ? 128 : vect->allocated * 2);
		void *new_array = realloc(vect->array, size * sizeof(void*));
		if (new_array == NULL) return 0;
		vect->array = (void**)new_array;
		vect->allocated = size;
	}

	vect->array[vect->size] = item;
	vect->size++;
	return 1;
}
