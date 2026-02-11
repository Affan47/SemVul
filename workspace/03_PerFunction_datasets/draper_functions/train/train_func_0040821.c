String_numOccurances(String * string, String * substring)
{
	int offset, occurances, position;

	if(string == NULL || substring == NULL)
		return -1;

	offset = 0;
	occurances = 0;

	while((position = List_positionOfSubListOffset(string->characters, substring->characters, compareCaseSensitive, offset)) != -1)
	{
		occurances++;
		offset = position + String_getLength(substring);
	}

	return occurances;
}
