IoXmlReader_parseString(IoXmlReader *self, IoObject *locals, IoMessage *m)
{
	IoObject *doc;
	COPY_ARG_TO(0, doc);
	if (ISSEQ(doc)) {
		DATA(self)->xmlText = doc;
		DATA(self)->reader = xmlReaderForMemory(ENSURE_CSTRING(doc),
												ENSURE_CSTRING(doc) ? IOSEQ_LENGTH(doc) : 0,
												ENSURE_CSTRING(DATA(self)->url),
												ENSURE_CSTRING(DATA(self)->encoding),
												DATA(self)->options);
	} else {
		IoState_error_(IOSTATE,m, "Sequence required");
	}
	if (!DATA(self)->reader)
		IoState_error_(IOSTATE,m,DATA(self)->error);
	xmlTextReaderSetErrorHandler(DATA(self)->reader, errorFunc, m);
	return self;
}
