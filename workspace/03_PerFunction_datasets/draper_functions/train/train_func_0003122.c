simple_hash_data(const unsigned char* buf, size_t len, uint32_t code)
{
	for (size_t i = 0; i < len; i++)
		code = ((code << 4) | (code >> (32 - 4))) ^ (uint32_t)buf[i];

	return code;
}
