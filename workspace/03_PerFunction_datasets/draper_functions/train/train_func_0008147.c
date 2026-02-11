String_toUpperCase(String * string)
{
	String * newString;
	ListIterator * iterator;
	char * character;

	if(string == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		*character = toupper(*character);
		character = ListIterator_nextItem(iterator);
	}

	ListIterator_destroy(iterator);
	return newString;
}
