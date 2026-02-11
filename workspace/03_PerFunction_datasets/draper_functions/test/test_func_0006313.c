make_tail_room(array_t *array, u_int8_t room)
{
	if (array->tail < room)
	{
		array->data = realloc(array->data,
						get_size(array, array->count + array->head + room));
		array->tail = room;
	}
}
