HexDecodeString(const char *hex)
{
	StringSource ss(hex, true, new HexDecoder);
	SecByteBlock result((size_t)ss.MaxRetrievable());
	ss.Get(result, result.size());
	return result;
}
