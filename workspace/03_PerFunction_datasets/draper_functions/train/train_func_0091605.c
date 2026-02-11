mono_aot_get_method_index (MonoMethod *method)
{
	g_assert (llvm_acfg);
	return get_method_index (llvm_acfg, method);
}
