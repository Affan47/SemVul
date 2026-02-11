ldr_be(UINT32 op)
{
	offs_t offs = SIMMVAL + RSVAL32;
	UINT64 temp = RDOUBLE(offs & ~7);
	if (RTREG)
	{
		if ((offs & 7) == 7) RTVAL64 = temp;
		else
		{
			UINT64 mask = ~((UINT64)0xff);
			int shift = 8 * (offs & 7);
			RTVAL64 = (RTVAL64 & (mask << shift)) | (temp >> (56 - shift));
		}
	}
}
