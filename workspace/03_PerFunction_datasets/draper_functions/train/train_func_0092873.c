vmci_handle_arr_append_entry(struct vmci_handle_arr **array_ptr,
				  struct vmci_handle handle)
{
	struct vmci_handle_arr *array = *array_ptr;

	if (unlikely(array->size >= array->capacity)) {

		struct vmci_handle_arr *new_array;
		size_t new_capacity = array->capacity * VMCI_ARR_CAP_MULT;
		size_t new_size = handle_arr_calc_size(new_capacity);

		new_array = krealloc(array, new_size, GFP_ATOMIC);
		if (!new_array)
			return;

		new_array->capacity = new_capacity;
		*array_ptr = array = new_array;
	}

	array->entries[array->size] = handle;
	array->size++;
}
