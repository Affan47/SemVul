prepend_attribute(const char_t* name_)
	{
		if (type() != node_element && type() != node_declaration) return xml_attribute();

		xml_attribute a(impl::allocate_attribute(impl::get_allocator(_root)));
		if (!a) return xml_attribute();

		a.set_name(name_);

		xml_attribute_struct* head = _root->first_attribute;

		if (head)
		{
			a._attr->prev_attribute_c = head->prev_attribute_c;
			head->prev_attribute_c = a._attr;
		}
		else
			a._attr->prev_attribute_c = a._attr;

		a._attr->next_attribute = head;
		_root->first_attribute = a._attr;

		return a;
	}
