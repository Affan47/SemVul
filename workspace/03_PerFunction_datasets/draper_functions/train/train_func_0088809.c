free_format(prt_fmt** ptr)
{
	prt_fmt** ptr2 = ptr;


	if (ptr == NULL)
		return;

	while(*ptr != NULL)
	{
		free((*ptr)->string);
		free((*ptr)->range);
		free((*ptr++));
	}

	free(ptr2);
	free(colsize);
	colsize = NULL;
}
