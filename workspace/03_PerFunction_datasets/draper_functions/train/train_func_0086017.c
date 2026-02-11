queryConvert(const unsigned char* bytes, int length) const
{
	if (1 <= length)
		return *bytes;
	else
		return -1;
}
