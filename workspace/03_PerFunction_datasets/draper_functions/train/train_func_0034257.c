icalarray_expand		(icalarray	*array,
				 int		 space_needed)
{
    int new_space_allocated;
    void *new_data;

    new_space_allocated = array->space_allocated + array->increment_size;

    if ((unsigned int)space_needed > array->increment_size)
	new_space_allocated += space_needed;


	new_data = malloc(new_space_allocated * array->element_size);

    if (new_data) {
	memcpy(new_data,array->data,array->element_size*array->space_allocated);
	free(array->data);
	array->data = new_data;
	array->space_allocated = new_space_allocated;
    } else {
	icalerror_set_errno(ICAL_ALLOCATION_ERROR);
    }
}
