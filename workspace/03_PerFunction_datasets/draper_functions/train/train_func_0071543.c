zero_out (region_ptr, size_in_bytes)
     char   *region_ptr;
     size_t size_in_bytes;
{
	register char *rp, *rp_end;

	rp = region_ptr;
	rp_end = region_ptr + size_in_bytes;

	while (rp < rp_end)
		*rp++ = 0;
}
