array_insert_enumerator(array_t *array, int idx, enumerator_t *enumerator)
{
	void *ptr;

	while (enumerator->enumerate(enumerator, &ptr))
	{
		array_insert(array, idx, ptr);
	}
	enumerator->destroy(enumerator);
}
