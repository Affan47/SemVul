as_bool(bool def) const
	{
		return impl::get_value_bool(_attr ? _attr->value : 0, def);
	}
