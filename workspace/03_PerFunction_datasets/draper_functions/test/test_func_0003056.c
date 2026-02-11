IoXmlReader_defaultAttrs(IoXmlReader *self, IoObject *locals, IoMessage *m)
{
	return DATA(self)->options & XML_PARSER_DEFAULTATTRS ? IOTRUE(self) : IOFALSE(self);
}
