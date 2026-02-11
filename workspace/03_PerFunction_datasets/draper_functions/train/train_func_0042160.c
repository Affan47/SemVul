convert_raw_attr_to_xml_func(void *val, void *data)
{
	struct conversion_data *cd = data;
	sdp_data_t *value = val;
	char buf[STRBUFSIZE];

	buf[STRBUFSIZE - 1] = '\0';
	snprintf(buf, STRBUFSIZE - 1, "\t<attribute id=\"0x%04x\">\n",
		 value->attrId);
	cd->appender(cd->data, buf);

	if (data)
		convert_raw_data_to_xml(value, 2, cd->data, cd->appender);
	else
		cd->appender(cd->data, "\t\tNULL\n");

	cd->appender(cd->data, "\t</attribute>\n");
}
