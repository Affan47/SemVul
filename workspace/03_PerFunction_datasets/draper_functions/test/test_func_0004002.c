ge2comp(s32 a, s32 width)
{
	if (width == 32)
		return a;
	else
		return (a >= (1 << (width - 1))) ? (a - (1 << width)) : a;
}
