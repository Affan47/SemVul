fpu__init_system_mxcsr(void)
{
	unsigned int mask = 0;

	if (cpu_has_fxsr) {

		static struct fxregs_state fxregs __initdata;

		asm volatile("fxsave %0" : "+m" (fxregs));

		mask = fxregs.mxcsr_mask;


		if (mask == 0)
			mask = 0x0000ffbf;
	}
	mxcsr_feature_mask &= mask;
}
