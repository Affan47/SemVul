swizzle_mask(unsigned swizzle, unsigned mask)
{
	unsigned ret = 0;
	for (unsigned chan = 0; chan < 4; ++chan) {
		unsigned swz = GET_SWZ(swizzle, chan);
		if (swz < 4)
			ret |= GET_BIT(mask, swz) << chan;
	}
	return ret;
}
