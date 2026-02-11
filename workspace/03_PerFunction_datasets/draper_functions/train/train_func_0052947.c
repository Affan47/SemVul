disable_pkg_thres_interrupt(void)
{
	u32 l, h;
	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
	wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT,
			l & (~THERM_INT_THRESHOLD0_ENABLE) &
				(~THERM_INT_THRESHOLD1_ENABLE), h);
}
