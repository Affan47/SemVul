comment(const XMLChar ch[], int start, int length)
{
	if (_unclosedStartTag) closeStartTag();
	prettyPrint();
	writeMarkup("<!--");
	while (length-- > 0) writeXML(ch[start++]);
	writeMarkup("-->");
	_contentWritten = false;
}
