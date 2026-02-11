IoXmlReader_parseFile(IoXmlReader *self, IoObject *locals, IoMessage *m)
{
	IoObject *file_or_filename;
	COPY_ARG_TO(0, file_or_filename);

	if (ISFILE(file_or_filename))
	{
		DATA(self)->xmlFile = file_or_filename;
		int fd = fileno(((IoFileData*)IoObject_dataPointer(file_or_filename))->stream);
		DATA(self)->reader = xmlReaderForFd(fd,
											ENSURE_CSTRING(DATA(self)->url),
											ENSURE_CSTRING(DATA(self)->encoding),
											DATA(self)->options);
	}
	else if (ISSEQ(file_or_filename))
	{
		DATA(self)->xmlPath = file_or_filename;
		DATA(self)->reader = xmlReaderForFile(ENSURE_CSTRING(file_or_filename),
												ENSURE_CSTRING(DATA(self)->encoding),
												DATA(self)->options);
	}
	else
	{
		IoState_error_(IOSTATE, m, "File or Sequence required");
	}

	if (!DATA(self)->reader)
		IoState_error_(IOSTATE,m,"Error Initializing Xml Parser");
	xmlTextReaderSetErrorHandler(DATA(self)->reader, errorFunc, self);
	return self;
}
