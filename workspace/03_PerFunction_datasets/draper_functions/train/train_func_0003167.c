find_child_by_attribute(const char_t* attr_name, const char_t* attr_value) const
	{
		if (!_root) return xml_node();

		for (xml_node_struct* i = _root->first_child; i; i = i->next_sibling)
			for (xml_attribute_struct* a = i->first_attribute; a; a = a->next_attribute)
				if (impl::strequal(attr_name, a->name) && impl::strequal(attr_value, a->value))
					return xml_node(i);

		return xml_node();
	}
