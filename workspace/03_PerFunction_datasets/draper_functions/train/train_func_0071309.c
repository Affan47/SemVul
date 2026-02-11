mono_jit_compile_method (MonoMethod *method)
{
	MonoException *ex = NULL;
	gpointer code;

	code = mono_jit_compile_method_with_opt (method, mono_get_optimizations_for_method (method, default_opt), &ex);
	if (!code) {
		g_assert (ex);
		mono_raise_exception (ex);
	}

	return code;
}
