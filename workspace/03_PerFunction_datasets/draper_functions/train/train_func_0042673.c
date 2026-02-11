sdr_le(UINT32 op)
{
	offs_t offs = SIMMVAL + RSVAL32;
	if (!(offs & 7)) WDOUBLE(offs, RTVAL64);
	else
	{
		UINT64 temp = RDOUBLE(offs & ~7);
		UINT64 mask = ~((UINT64)0xff << 56);
		int shift = 8 * (offs & 7);
		WDOUBLE(offs & ~7, (temp & (mask >> (56 - shift))) | (RTVAL64 << shift));
	}
}
