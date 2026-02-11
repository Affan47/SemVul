wi_array_init_with_arguments(wi_array_t *array, va_list ap) {
	void	*data;

	array = wi_array_init(array);

	while((data = va_arg(ap, void *)))
		_wi_array_add_data(array, data);

	return array;
}
