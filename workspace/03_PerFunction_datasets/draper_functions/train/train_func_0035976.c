IoXmlWriter_writeDTDExternalEntityContents(IoXmlWriter *self, IoObject *locals, IoMessage *m)
{
	const char *pubid = IoMessage_locals_cStringArgAtOrNULL_(m, locals, 0);
	const char *sysid = IoMessage_locals_cStringArgAtOrNULL_(m, locals, 1);
	const char *ndataid = IoMessage_locals_cStringArgAtOrNULL_(m, locals, 2);

	ENSURE_OPEN;
	int rc = xmlTextWriterWriteDTDExternalEntityContents(DATA(self)->writer, (xmlChar*)pubid, (xmlChar*)sysid, (xmlChar*)ndataid);
	IoXmlWriter_raiseErrors_(self, m, rc);

	return self;
}
