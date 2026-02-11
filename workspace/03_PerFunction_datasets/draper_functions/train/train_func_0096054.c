wi_enumerator_array_data_enumerator(wi_runtime_instance_t *instance, wi_enumerator_context_t *context) {
	wi_array_t		*array = instance;
	void			*data;

	if(context->index == array->data_count)
		return NULL;

	data = wi_array_data_at_index(array, context->index);

	context->index++;

	return data;
}
