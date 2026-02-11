swf_read_sint(SWFReader *read, u32 nbBits)
{
	s32 r = 0;
	u32 i;
	if (!nbBits)return 0;
	r = -1 * (s32) swf_read_int(read, 1);
	for (i=1; i<nbBits; i++){
		r <<= 1;
		r |= swf_read_int(read, 1);
	}
	return r;
}
