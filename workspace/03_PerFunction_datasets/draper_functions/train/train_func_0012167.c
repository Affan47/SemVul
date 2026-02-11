WriteTextNode(const std::string& value)
	{
		pugi::xml_document d;
		pugi::xml_node n = d.append_child(pugi::node_pcdata);
		n.set_value(value.c_str());
		d.save(os, "", pugi::format_no_declaration | pugi::format_raw, pugi::encoding_utf8);
	}
