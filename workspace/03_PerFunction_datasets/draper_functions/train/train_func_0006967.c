translate_strq_swizzle(unsigned int swizzle)
{
	unsigned int swiz = 0;
	int i;
	for (i = 0; i < 4; i++)
		swiz |= (GET_SWZ(swizzle, i) & 0x3) << i*2;
	return swiz;
}
