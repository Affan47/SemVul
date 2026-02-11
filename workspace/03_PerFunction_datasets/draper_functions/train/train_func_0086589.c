sdp_xml_data_alloc(void)
{
	struct sdp_xml_data *elem;

	elem = malloc(sizeof(struct sdp_xml_data));
	if (!elem)
		return NULL;

	memset(elem, 0, sizeof(struct sdp_xml_data));


	elem->size = DEFAULT_XML_DATA_SIZE;
	elem->text = malloc(DEFAULT_XML_DATA_SIZE);
	elem->text[0] = '\0';

	return elem;
}
