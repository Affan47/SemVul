toArray() const
{
	ANTLR_USE_NAMESPACE(std)vector<unsigned int> elems;
	for (unsigned int i = 0; i < storage.size(); i++)
	{
		if (storage[i])
			elems.push_back(i);
	}

	return elems;
}
