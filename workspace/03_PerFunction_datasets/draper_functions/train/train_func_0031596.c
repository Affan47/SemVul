json_index(const json *ptr, size_t idx)
{
	json *j = (json*)ptr;

	if (!j)
		return NULL;

	while (j)
	{
		if (idx-- == 0)
			return j;

		j = j->next;
	}

	return NULL;
}
