SizeGF_IPMPX_KeyData(GF_IPMPX_Data *_p)
{
	u32 size = 0;
	GF_IPMPX_KeyData*p = (GF_IPMPX_KeyData*)_p;
	size += GF_IPMPX_GetByteArraySize(p->keyBody);
	size += 1;
	if (p->flags & (1)) size += 8;
	if (p->flags & (1<<1)) size += 4;
	if (p->flags & (1<<2)) size += 8;
	if (p->flags & (1<<3)) size += 4;
	size += GF_IPMPX_GetByteArraySize(p->OpaqueData);
	return size;
}
