parse_xml_set_error(char *mesg)
{

  if (parse_xml_parser == NULL)
	return;

  if (mesg != NULL)
	parse_xml_error.mesg = mesg;
  else {
	enum XML_Error code;

	if ((code = XML_GetErrorCode(parse_xml_parser)) != XML_ERROR_NONE)
	  parse_xml_error.mesg = (char *) XML_ErrorString(code);
	else
	  parse_xml_error.mesg = "XML parse error";
  }

  parse_xml_error.line = XML_GetCurrentLineNumber(parse_xml_parser);
  parse_xml_error.pos = XML_GetCurrentColumnNumber(parse_xml_parser);
}
