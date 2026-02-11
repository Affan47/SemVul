debug_wgetpeekdma (uaecptr addr, uae_u32 v)
{
	uae_u32 vv = v;
	if (!memwatch_enabled)
		return v;
	memwatch_func (addr, 1, 2, &vv);
	return vv;
}
