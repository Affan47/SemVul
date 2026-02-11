x86_noinvpcid_setup(char *s)
{

	if (s)
		return -EINVAL;


	if (!boot_cpu_has(X86_FEATURE_INVPCID))
		return 0;

	setup_clear_cpu_cap(X86_FEATURE_INVPCID);
	pr_info("noinvpcid: INVPCID feature disabled\n");
	return 0;
}
