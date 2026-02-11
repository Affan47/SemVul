add_section(std::vector<std::string> &returnList, CL_DomElement &sectionElement, const std::string &section_name)
{
	for (CL_DomNode node = sectionElement.get_first_child(); !node.is_null(); node = node.get_next_sibling())
	{
		if (!node.is_element()) continue;

		CL_DomElement element = node.to_element();
		if (element.get_tag_name() == "section")
		{
			if (sectionElement.get_attribute("name") == section_name)
				returnList.push_back(element.get_attribute("name"));
			add_section(returnList, element, section_name);
		}
	}
}
