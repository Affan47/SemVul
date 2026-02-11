String_stripChars(String * string, List * chars)
{
	String * newString;
	ListIterator * iterator;
	char * character;

	if(string == NULL || chars == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		if(List_containsMatchedData(chars, character, compareCaseSensitive))
		{
			ListIterator_removeCurrent(iterator);
			free(character);
			character = ListIterator_currentValue(iterator);
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return newString;
}
