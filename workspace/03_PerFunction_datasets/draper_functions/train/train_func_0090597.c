Sorting_isSorted(SDSort *self, size_t size)
{
	SDSortCompareCallback *comp = self->comp;
	void *context = self->context;
	size_t i;

	for (i = 0; i + 1 < size; i ++)
	{
		if ((*comp)(context, i, i + 1) > 0)
		{
			return 0;
		}
	}

	return 1;
}
