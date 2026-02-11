arrayToString(const MemoryRegion &a)
{
	return QString::fromLatin1(encode(a).toByteArray());
}
