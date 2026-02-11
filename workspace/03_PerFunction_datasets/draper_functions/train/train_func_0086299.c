vxt_contence(void *data, const XML_Char *string, int len)
{
	XMLReader *c;
	c = static_cast <XMLReader *>(data);

	std::string str = std::string(string, 0 , len );

	c->current_xml_tag->AddText(str);
}
