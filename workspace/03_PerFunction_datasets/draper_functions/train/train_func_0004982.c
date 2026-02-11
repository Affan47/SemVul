mthca_array_init(struct mthca_array *array, int nent)
{
	int npage = (nent * sizeof (void *) + PAGE_SIZE - 1) / PAGE_SIZE;
	int i;

	array->page_list = kmalloc(npage * sizeof *array->page_list, GFP_KERNEL);
	if (!array->page_list)
		return -ENOMEM;

	for (i = 0; i < npage; ++i) {
		array->page_list[i].page = NULL;
		array->page_list[i].used = 0;
	}

	return 0;
}
