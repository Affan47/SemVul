end_string_at_first_hash_symbol(SCP_string &src)
{
	int index = get_index_of_first_hash_symbol(src);
	if (index >= 0)
	{
		while (index > 0 && src[index-1] == ' ')
			index--;

		src.resize(index);
		return true;
	}

	return false;
}
