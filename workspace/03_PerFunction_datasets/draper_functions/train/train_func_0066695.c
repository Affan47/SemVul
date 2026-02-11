request_data_reference(REQUEST *request,
		       void *unique_ptr, int unique_int)
{
	request_data_t **last;

	for (last = &(request->data); *last != NULL; last = &((*last)->next)) {
		if (((*last)->unique_ptr == unique_ptr) &&
		    ((*last)->unique_int == unique_int)) {
			request_data_t *this = *last;
			void *ptr = this->opaque;

			return ptr;
		}
	}

	return NULL;
}
