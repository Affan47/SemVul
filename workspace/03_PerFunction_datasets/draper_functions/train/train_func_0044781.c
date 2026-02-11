substringData(unsigned long offset, unsigned long count) const
{
	if (offset >= _data.length())
		throw DOMException(DOMException::INDEX_SIZE_ERR);

	return _data.substr(offset, count);
}
