register_method_local (MonoProfiler *prof, MonoMethod *method, MonoJitInfo *ji)
{
	if (!mono_conc_hashtable_lookup (prof->method_table, method)) {


		MethodInfo *info = (MethodInfo *)malloc (sizeof (MethodInfo));

		info->method = method;
		info->ji = ji;
		info->time = current_time ();

		g_ptr_array_add (TLS_GET (GPtrArray, tlsmethodlist), info);
	}
}
