_param_string_values_cmp (GParamSpec *pspec, const GValue *value1, const GValue *value2)
{
	if (!value1->data[0].v_pointer)
		return value2->data[0].v_pointer != NULL ? -1 : 0;
	else if (!value2->data[0].v_pointer)
		return value1->data[0].v_pointer != NULL;
	else
		return strcmp (value1->data[0].v_pointer, value2->data[0].v_pointer);
}
