seaudit_sort_destroy(seaudit_sort_t ** sort)
{
	if (sort != NULL && *sort != NULL) {
		free(*sort);
		*sort = NULL;
	}
}
