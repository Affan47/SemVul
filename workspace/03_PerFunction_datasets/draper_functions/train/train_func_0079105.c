IoXmlWriter_openStandardOut(IoXmlWriter *self, IoObject *locals, IoMessage *m)
{
	xmlCharEncodingHandlerPtr encoding = xmlFindCharEncodingHandler("UTF-8");
	IOASSERT(encoding, "Encoding is null.");
	xmlOutputBufferPtr buffer = xmlOutputBufferCreateFile(stdout, encoding);
	IOASSERT(buffer, "buffer is null.");
	DATA(self)->writer = xmlNewTextWriter(buffer);
	return self;
}
