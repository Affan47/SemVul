ves_icall_System_Runtime_InteropServices_Marshal_PtrToStringUni (guint16 *ptr)
{
	MonoDomain *domain = mono_domain_get ();
	int len = 0;
	guint16 *t = ptr;

	MONO_ARCH_SAVE_REGS;

	if (ptr == NULL)
		return NULL;

	while (*t++)
		len++;

	return mono_string_new_utf16 (domain, ptr, len);
}
