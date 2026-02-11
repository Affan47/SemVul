as_float(float def) const
	{
		return impl::get_value_float(_attr ? _attr->value : 0, def);
	}
