writecache_be_dword(offs_t offset, data32_t data)
{
	offset &= 0x1fffffff;
	if (offset * 4 < r3000.cache_size) *(data32_t *)&r3000.cache[offset] = data;
}
