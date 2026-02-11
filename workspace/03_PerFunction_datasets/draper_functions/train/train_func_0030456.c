String_containsNotMatching(String * string, int (*isEqual)(int))
{
	Boolean contains;
	ListIterator * iterator;
	char * character;
	iterator = ListIterator_create(string->characters);
	character = ListIterator_seekToFirst(iterator);

	contains = false;
	while(character != NULL)
	{
		if(!isEqual(*character))
		{
			contains = true;
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return contains;
}
