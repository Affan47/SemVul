get_string_offset
	(
	)
	{
	if (offset < 0)

		offset = fun->find_string_prefix(*this, prefix.c_str());
	return offset;
	}
