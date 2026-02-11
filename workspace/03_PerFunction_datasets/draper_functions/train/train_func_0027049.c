allow_insert_child(xml_node_type parent, xml_node_type child)
	{
		if (parent != node_document && parent != node_element) return false;
		if (child == node_document || child == node_null) return false;
		if (parent != node_document && (child == node_declaration || child == node_doctype)) return false;

		return true;
	}
