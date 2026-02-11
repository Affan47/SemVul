stringListIndex (
		const stringList *const current,
		const char *const string,
		boolean (*test)(const char *s, vString *const vs))
{
	int result = -1;
	unsigned int i;
	Assert (current != NULL);
	Assert (string != NULL);
	Assert (test != NULL);
	for (i = 0  ;  result == -1  &&  i < current->count  ;  ++i)
		if ((*test)(string, current->list [i]))
			result = i;
	return result;
}
