clipping(s32 x, s32 min, s32 max) {
#if 1 || defined(SIGNED_IS_NOT_2S_COMPLEMENT)
	if (x < min)
	{
		return (min);
	}
	else if (x > max)
	{
		return (max);
	}
	return (x);
#else
	return x ^ ((-(x < min)) & (x ^ min)) ^ ((-(x > max)) & (x ^ max));
#endif
}
