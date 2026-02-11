mono_assembly_load_full (MonoAssemblyName *aname, const char *basedir, MonoImageOpenStatus *status, gboolean refonly)
{
	MonoAssembly *result = mono_assembly_load_full_nosearch (aname, basedir, status, refonly);

	if (!result)

		result = mono_assembly_invoke_search_hook_internal (aname, refonly, TRUE);
	return result;
}
