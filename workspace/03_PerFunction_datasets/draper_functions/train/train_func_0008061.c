GB_NewArray(void *pdata, int size, int count)
{
	ARRAY_create_with_size(pdata, size, 16);
	if (count)
		ARRAY_add_data(pdata, count, TRUE);
}
