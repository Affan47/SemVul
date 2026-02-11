readFieldValue (
	const tagEntry *const entry, const char *const key)
{
	const char *result = NULL;
	int i;
	if (strcmp (key, "kind") == 0)
		result = entry->kind;
	else if (strcmp (key, "file") == 0)
		result = EmptyString;
	else for (i = 0  ;  i < entry->fields.count  &&  result == NULL  ;  ++i)
		if (strcmp (entry->fields.list [i].key, key) == 0)
			result = entry->fields.list [i].value;
	return result;
}
