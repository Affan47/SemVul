json_array_add_value(struct json_array *array, struct json_value *value)
{
	struct json_value **values = realloc(array->values,
		sizeof(struct json_value *) * (array->value_cnt + 1));

	if (!values)
		return ENOMEM;
	values[array->value_cnt] = value;
	array->value_cnt++;
	array->values = values;

	value->parent_type = JSON_PARENT_TYPE_ARRAY;
	value->parent_array = array;
	return 0;
}
