IoXmlReader_moveToAttributeNs(IoXmlReader *self, IoObject *locals, IoMessage *m)
{
	ENSURE_OPEN;
	IoObject *localName, *namespaceURI;
	COPY_ARG_TO(0, localName);
	COPY_ARG_TO(1, namespaceURI);
	int ret = xmlTextReaderMoveToAttributeNs(DATA(self)->reader, (xmlChar*)ENSURE_CSTRING(localName), (xmlChar*)ENSURE_CSTRING(namespaceURI));
	if (ret < 0) IoXmlReader_raiseError(self, m);
	return ret == 0 ? IOFALSE(self) : IOTRUE(self);
}
