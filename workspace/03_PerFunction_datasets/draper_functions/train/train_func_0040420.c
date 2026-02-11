as_string(const char_t* def) const
	{
		xml_node_struct* d = _data();

		return (d && d->value) ? d->value : def;
	}
