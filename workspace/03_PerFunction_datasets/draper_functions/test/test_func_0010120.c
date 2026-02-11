reg_is_softreg (int reg, const char spec)
{
	return (spec == 'i' && reg >= MONO_MAX_IREGS)
		|| (spec == 'f' && reg >= MONO_MAX_FREGS)
#ifdef MONO_ARCH_SIMD_INTRINSICS
		|| (spec == 'x' && reg >= MONO_MAX_XREGS)
#endif
		|| (spec == 'v');
}
