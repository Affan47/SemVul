append_child(xml_node_type type_)
	{
		if (!impl::allow_insert_child(this->type(), type_)) return xml_node();

		xml_node n(impl::append_node(_root, impl::get_allocator(_root), type_));

		if (type_ == node_declaration) n.set_name(PUGIXML_TEXT("xml"));

		return n;
	}
