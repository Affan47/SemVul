ib_vector_push(

	ib_vector_t*	vec,
	void*		elem)
{
	if (vec->used >= vec->total) {
		void**	new_data;
		ulint	new_total = vec->total * 2;

		new_data = mem_heap_alloc(vec->heap,
					  sizeof(void*) * new_total);
		memcpy(new_data, vec->data, sizeof(void*) * vec->total);

		vec->data = new_data;
		vec->total = new_total;
	}

	vec->data[vec->used] = elem;
	vec->used++;
}
