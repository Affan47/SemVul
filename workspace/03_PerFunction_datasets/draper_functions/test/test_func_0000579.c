sgmlExtensionOnDivert(struct _sgml_parser *parser, unsigned long newIndex, unsigned long oldState, unsigned long newState, const char *lastBuffer, unsigned long lastBufferSize)
{
	SGML_EXTENSION_HTML *ext = (SGML_EXTENSION_HTML *)sgmlParserGetUserContext(parser);

	if ((oldState & SGML_PARSER_STATE_INELEMENT) && (newState & SGML_PARSER_STATE_INTEXT))
	{


		if (oldState & SGML_PARSER_STATE_INATTRIBUTENAME_ACTUAL)
		{
			sgmlExtensionHtmlAttributeNew(parser, sgmlParserGetUserContext(parser), lastBuffer, "");
			ext->skipNextAttribute = 1;
		}
 		if (oldState & SGML_PARSER_STATE_INATTRIBUTEVALUE_S)
		{
			sgmlExtensionHtmlAttributeNew(parser, sgmlParserGetUserContext(parser), parser->internal.lastAttributeName, lastBuffer);
			ext->skipNextAttribute = 1;
		}

		if ((ext->currElement) && (ext->currElement->autoclose))
			ext->currElement = (ext->currElement)?ext->currElement->parent:NULL;

		while ((ext->currElement) && (ext->currElement->deferredClosure))
			ext->currElement = ext->currElement->parent;
	}

	ext->saveDivert(parser, newIndex, oldState, newState, lastBuffer, lastBufferSize);
}
