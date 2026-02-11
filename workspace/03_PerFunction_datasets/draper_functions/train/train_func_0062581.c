ves_icall_System_Math_Log (gdouble x)
{
	MONO_ARCH_SAVE_REGS;

	if (x == 0)
		return -HUGE_VAL;
	else if (x < 0)
		return NAN;

	return log (x);
}
