check_loader_disabled_bsp(void)
{
	u32 a, b, c, d;
#ifdef CONFIG_X86_32
	const char *cmdline = (const char *)__pa_nodebug(boot_command_line);
	const char *opt	    = "dis_ucode_ldr";
	const char *option  = (const char *)__pa_nodebug(opt);
	bool *res = (bool *)__pa_nodebug(&dis_ucode_ldr);

#else
	const char *cmdline = boot_command_line;
	const char *option  = "dis_ucode_ldr";
	bool *res = &dis_ucode_ldr;
#endif

	if (!have_cpuid_p())
		return *res;

	a = 1;
	c = 0;
	native_cpuid(&a, &b, &c, &d);


	if (c & BIT(31))
		return *res;

	if (cmdline_find_option_bool(cmdline, option) <= 0)
		*res = false;

	return *res;
}
