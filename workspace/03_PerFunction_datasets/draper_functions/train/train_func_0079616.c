ves_icall_System_AppDomain_InternalUnload (gint32 domain_id)
{
	MonoDomain * domain = mono_domain_get_by_id (domain_id);

	MONO_ARCH_SAVE_REGS;

	if (NULL == domain) {
		MonoException *exc = mono_get_exception_execution_engine ("Failed to unload domain, domain id not found");
		mono_raise_exception (exc);
	}

	if (domain == mono_get_root_domain ()) {
		mono_raise_exception (mono_get_exception_cannot_unload_appdomain ("The default appdomain can not be unloaded."));
		return;
	}


	if (g_getenv ("MONO_NO_UNLOAD"))
		return;
#ifdef __native_client__
	return;
#endif

	mono_domain_unload (domain);
}
