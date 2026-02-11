arch_init(void)
{
	insn_sanity_check();

	setup_fpu();

	init_cpu_features();

	if (!cpu_has(X86_FEATURE_SSE))
		warn("CPU does not support SSE. Floating point arithmetic will not work.");
}
