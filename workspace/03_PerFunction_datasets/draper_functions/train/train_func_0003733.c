array_convert(CARRAY *src, CLASS *class)
{
	CARRAY *array;
	int i;
	void *data;
	VALUE temp;

	if (!CLASS_inherits(class, CLASS_Array))
		return NULL;

	_converted_array = array = OBJECT_create(class, NULL, NULL, 0);

	ARRAY_add_many_void(&array->data, src->count);
	array->count = src->count;

	ON_ERROR(error_array_convert)
	{
		for (i = 0; i < src->count; i++)
		{
			data = CARRAY_get_data(src, i);
			VALUE_read(&temp, data, src->type);
			BORROW(&temp);
			data = CARRAY_get_data(array, i);
			VALUE_write(&temp, data, array->type);
			RELEASE(&temp);
		}
	}
	END_ERROR

	return array;
}
