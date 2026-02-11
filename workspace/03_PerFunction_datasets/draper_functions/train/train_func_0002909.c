findHeader(const string &line, int i,
                                       const vector<const string*>* possibleHeaders) const
{
	assert(isCharPotentialHeader(line, i));

	size_t maxHeaders = possibleHeaders->size();
	for (size_t p = 0; p < maxHeaders; p++)
	{
		const string* header = (*possibleHeaders)[p];
		const size_t wordEnd = i + header->length();
		if (wordEnd > line.length())
			continue;
		int result = (line.compare(i, header->length(), *header));
		if (result > 0)
			continue;
		if (result < 0)
			break;

		if (wordEnd == line.length())
			return header;
		if (isLegalNameChar(line[wordEnd]))
			continue;
		const char peekChar = peekNextChar(line, wordEnd - 1);

		if (peekChar == ',' || peekChar == ')')
			break;


		else if ((header == &AS_GET || header == &AS_SET || header == &AS_DEFAULT)
		         && (peekChar == ';' ||  peekChar == '(' || peekChar == '='))
			break;
		return header;
	}
	return NULL;
}
