IoHttpParser_rawParse(IoHttpParser *self, IoObject *locals, IoMessage *m)
{

	HttpParser *parser = PARSER(self);
	IoSeq *parseBuffer = IoObject_getSlot_(self, IOSYMBOL("parseBuffer"));
	IoMap *httpFields = IoObject_getSlot_(self, IOSYMBOL("httpFields"));

	IOASSERT(ISSEQ(parseBuffer), "The parseBuffer should be set to a Sequence before parse is called.");
	IOASSERT(IoSeq_rawSize(parseBuffer) > 0, "The parseBuffer can't be empty when parse is called.");

	IOASSERT(ISMAP(httpFields), "httpFields should be set to a Map before parse is called.");

	HttpParser_parse_fromBuffer_givenLength_(parser, self, IoSeq_asCString(parseBuffer), IoSeq_rawSizeInBytes(parseBuffer));

	if (HttpParser_bytesParsed(parser) > MAX_HEADER_LENGTH)
	{
		return IoError_newWithMessageFormat_(IOSTATE, "Header is longer than the allowed length of %d bytes.", MAX_HEADER_LENGTH);
	}

	if (HttpParser_parseErrorOccured(parser))
	{
		UArray *parseError = HttpParser_parseError(parser);
		if (parseError)
		{
			return IoError_newWithMessageFormat_(IOSTATE, UArray_asCString(parseError));
		}
		else
		{
			return IoError_newWithMessageFormat_(IOSTATE, "Invalid Http format.  Parse failed.");
		}
	}

	return self;
}
