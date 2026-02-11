mem_obj_allocate(seg_manager_t *self, seg_id_t segid, int hash_id, mem_obj_enum type)
{
	mem_obj_t* mem = ( mem_obj_t* ) sci_calloc( sizeof (mem_obj_t), 1 );
	if( !mem ) {
		sciprintf( "seg_manager.c: invalid mem_obj " );
		return NULL;
	}

	if (segid >= self->heap_size) {
		void *temp;
		int oldhs = self->heap_size;

		if (segid >= self->heap_size * 2) {
			sciprintf( "seg_manager.c: hash_map error or others??" );
			return NULL;
		}
		self->heap_size *= 2;
		temp = sci_realloc ((void*)self->heap, self->heap_size * sizeof( mem_obj_t* ) );
		if (!temp) {
			sciprintf("seg_manager.c: Not enough memory space for script size" );
			return NULL;
		}
		self->heap = (mem_obj_t**)  temp;


		memset(self->heap + oldhs, 0, sizeof(mem_obj_t *) * (self->heap_size - oldhs));
	}

	mem->segmgr_id = hash_id;
	mem->type = type;


	self->heap[segid] = mem;
	return mem;
}
