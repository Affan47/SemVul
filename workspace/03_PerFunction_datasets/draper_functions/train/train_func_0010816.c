parse(std::string data) {
	orderlineno = atoi(xml_parse_tag(data, "OrderLineNo").c_str());
	std::string s_article = xml_parse_tag(data, "Article");
	article.parse(s_article);
	int ret = 1;
	while(ret) {
		std::string s_barcode = xml_parse_tag(data, "Barcode");
		if(strlen(s_barcode.c_str()) > 0) {
			Barcode b;
			b.parse(s_barcode);
			barcode.push_back(b);
		}
		ret = xml_parse_remove_first_tag(&data, "Barcode");
	}
	return strlen(data.c_str());
}
