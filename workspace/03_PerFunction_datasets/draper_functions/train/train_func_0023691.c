K053250_unpack_pixels(int region)
{
	UINT8 *src_ptr, *dst_ptr;
	int hi_nibble, lo_nibble, offset;

	dst_ptr = src_ptr = memory_region(region);
	offset = memory_region_length(region) / 2 - 1;

	do
	{
		lo_nibble = hi_nibble = src_ptr[offset];
		hi_nibble >>= 4;
		lo_nibble &= 0xf;
		dst_ptr[offset*2  ] = hi_nibble;
		dst_ptr[offset*2+1] = lo_nibble;
	}
	while ((--offset) >= 0);
}
