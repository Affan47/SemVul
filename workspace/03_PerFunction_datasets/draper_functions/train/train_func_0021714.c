parse(std::string data) {
	if(strcmp(xml_parse_tag(data, "FamilyGrouping").c_str(), "True") == 0)
		familygrouping = true;
	if(strcmp(xml_parse_tag(data, "Ranking").c_str(), "True") == 0)
		ranking = true;
	return strlen(data.c_str());
}
