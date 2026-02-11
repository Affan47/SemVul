parse(std::string data) {
	x = atoi(xml_parse_tag(data, "X").c_str());
	y = atoi(xml_parse_tag(data, "Y").c_str());
	z = atoi(xml_parse_tag(data, "Z").c_str());
	return strlen(data.c_str());
}
