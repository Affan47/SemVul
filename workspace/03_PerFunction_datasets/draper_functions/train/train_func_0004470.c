Get_Next(DictionaryCursor& cursor) const
{
    while (cursor.currentDictionaryEntry == NULL ||
	   cursor.currentDictionaryEntry->next == NULL)
    {
	cursor.currentTableIndex++;

	if (cursor.currentTableIndex >= tableLength)
	{
	    cursor.currentTableIndex--;
	    return NULL;
	}

	cursor.currentDictionaryEntry = table[cursor.currentTableIndex];

	if (cursor.currentDictionaryEntry != NULL)
	{
	    return cursor.currentDictionaryEntry->key;
	}
    }

    cursor.currentDictionaryEntry = cursor.currentDictionaryEntry->next;
    return cursor.currentDictionaryEntry->key;
}
