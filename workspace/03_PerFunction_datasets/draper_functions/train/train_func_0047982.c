mono_marshal_remoting_find_in_cache (MonoMethod *method, int wrapper_type)
{
	MonoMethod *res = NULL;
	MonoRemotingMethods *wrps = NULL;

	mono_marshal_lock_internal ();
	if (mono_method_get_wrapper_cache (method)->remoting_invoke_cache)
		wrps = (MonoRemotingMethods *)g_hash_table_lookup (mono_method_get_wrapper_cache (method)->remoting_invoke_cache, method);

	if (wrps) {
		switch (wrapper_type) {
		case MONO_WRAPPER_REMOTING_INVOKE: res = wrps->invoke; break;
		case MONO_WRAPPER_REMOTING_INVOKE_WITH_CHECK: res = wrps->invoke_with_check; break;
		case MONO_WRAPPER_XDOMAIN_INVOKE: res = wrps->xdomain_invoke; break;
		case MONO_WRAPPER_XDOMAIN_DISPATCH: res = wrps->xdomain_dispatch; break;
		}
	}


	mono_marshal_unlock_internal ();
	return res;
}
