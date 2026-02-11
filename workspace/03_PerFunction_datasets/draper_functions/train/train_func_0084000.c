accounts_list_free(char ***accounts_array)
{
	int i;

	if (*accounts_array == NULL)
		return;
	for (i = 0; accounts_array[0][i]; i++)
		xfree(accounts_array[0][i]);
	xfree(*accounts_array);
}
