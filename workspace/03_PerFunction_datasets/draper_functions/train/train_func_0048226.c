listStringCompare(void *data, void *key)
{
	ReturnErrIf(data == NULL);
	ReturnErrIf(key == NULL);

	if(!strcmp((char *)data, (char *)key)) {
		return LIST_FIND_MATCH;
	}

	return LIST_FIND_NOTAMATCH;
}
