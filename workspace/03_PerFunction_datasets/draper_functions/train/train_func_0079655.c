operator==(const MemoryRegion &other) const
{
	if(this == &other)
		return true;
	if(size() == other.size() && memcmp(data(), other.data(), size()) == 0)
		return true;
	return false;
}
