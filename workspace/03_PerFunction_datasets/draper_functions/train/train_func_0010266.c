xkl_lists_equal(gchar ** items1, gchar ** items2)
{
	if (items1 == items2)
		return TRUE;

	if ((items1 == NULL && items2 != NULL) ||
	    (items1 != NULL && items2 == NULL))
		return FALSE;

	while (*items1 != NULL && *items2 != NULL)
		if (!xkl_strings_equal(*items1++, *items2++))
			return FALSE;

	return (*items1 == NULL && *items2 == NULL);
}
