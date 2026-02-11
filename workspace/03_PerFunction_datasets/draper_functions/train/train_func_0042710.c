lookup_method_inner (MonoDomain *domain, MonoMethod *method)
{
	MonoJitInfo *ji = mono_internal_hash_table_lookup (&domain->jit_code_hash, method);

	if (ji)
		return ji;

	if (!mono_method_is_generic_sharable (method, FALSE))
		return NULL;
	return mono_domain_lookup_shared_generic (domain, method);
}
