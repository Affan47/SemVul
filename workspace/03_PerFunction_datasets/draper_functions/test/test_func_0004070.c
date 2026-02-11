array_remove_quoted_nulls(array)
ARRAY	*array;
{
	ARRAY_ELEMENT	*a;
	char	*t;

	if (array == 0 || array_head(array) == 0 || array_empty(array))
		return (ARRAY *)NULL;
	for (a = element_forw(array->head); a != array->head; a = element_forw(a))
		a->value = remove_quoted_nulls (a->value);
	return array;
}
