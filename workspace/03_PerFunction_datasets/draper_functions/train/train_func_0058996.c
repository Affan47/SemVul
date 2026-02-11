that_output(index, capital)
	 int             index;
	 int             capital;
{
	if (object[index]->attributes & PLURAL) {
		strcpy(temp_buffer, cstring_resolve("THOSE_WORD")->value);
	} else {
		strcpy(temp_buffer, cstring_resolve("THAT_WORD")->value);
	}

	if (capital)
		temp_buffer[0] = toupper(temp_buffer[0]);

	return temp_buffer;
}
