sm_destroy (seg_manager_t* self) {
	int i;

	for (i = 0; i < self->heap_size; i++) {
		if (self->heap[i])
			_sm_deallocate(self, i, 0);
	}

	free_int_hash_map(self->id_seg_map);

	sci_free (self->heap);
	self->heap = NULL;
}
