reallot_array(F_ARRAY* array, CELL capacity, CELL fill)
{
	int i;
	F_ARRAY* new_array;

	CELL to_copy = array_capacity(array);
	if(capacity < to_copy)
		to_copy = capacity;

	REGISTER_UNTAGGED(array);
	REGISTER_ROOT(fill);

	new_array = allot_array_internal(untag_header(array->header),capacity);

	UNREGISTER_ROOT(fill);
	UNREGISTER_UNTAGGED(array);

	memcpy(new_array + 1,array + 1,to_copy * CELLS);

	for(i = to_copy; i < capacity; i++)
		set_array_nth(new_array,i,fill);

	return new_array;
}
