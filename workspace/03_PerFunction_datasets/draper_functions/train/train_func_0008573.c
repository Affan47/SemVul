mono_security_core_clr_class_level_no_platform_check (MonoClass *klass)
{
	MonoSecurityCoreCLRLevel level = MONO_SECURITY_CORE_CLR_TRANSPARENT;
	MonoCustomAttrInfo *cinfo = mono_custom_attrs_from_class (klass);
	if (cinfo) {
		level = mono_security_core_clr_level_from_cinfo (cinfo, klass->image);
		mono_custom_attrs_free (cinfo);
	}

	if (level == MONO_SECURITY_CORE_CLR_TRANSPARENT && klass->nested_in)
		level = mono_security_core_clr_class_level_no_platform_check (klass->nested_in);

	return level;
}
