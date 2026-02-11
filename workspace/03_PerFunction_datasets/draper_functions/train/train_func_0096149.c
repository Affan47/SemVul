xen_enable_sysenter(void)
{
	int ret;
	unsigned sysenter_feature;

#ifdef CONFIG_X86_32
	sysenter_feature = X86_FEATURE_SEP;
#else
	sysenter_feature = X86_FEATURE_SYSENTER32;
#endif

	if (!boot_cpu_has(sysenter_feature))
		return;

	ret = register_callback(CALLBACKTYPE_sysenter, xen_sysenter_target);
	if(ret != 0)
		setup_clear_cpu_cap(sysenter_feature);
}
