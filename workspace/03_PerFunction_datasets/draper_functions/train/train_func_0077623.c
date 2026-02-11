is_corlib_asyncresult (MonoDomain *domain, MonoClass *klass)
{
	check_corlib_type_cached (domain, klass, "System.Runtime.Remoting.Messaging", "AsyncResult", &domain->corlib_asyncresult_class);
}
