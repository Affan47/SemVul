mono_domain_foreach (MonoDomainFunc func, gpointer user_data)
{
	int i, size;
	MonoDomain **copy;


	mono_appdomains_lock ();
	size = appdomain_list_size;
	copy = (MonoDomain **)mono_gc_alloc_fixed (appdomain_list_size * sizeof (void*), MONO_GC_DESCRIPTOR_NULL, MONO_ROOT_SOURCE_DOMAIN, "temporary domains list");
	memcpy (copy, appdomains_list, appdomain_list_size * sizeof (void*));
	mono_appdomains_unlock ();

	for (i = 0; i < size; ++i) {
		if (copy [i])
			func (copy [i], user_data);
	}

	mono_gc_free_fixed (copy);
}
