mono_domain_assembly_open (MonoDomain *domain, const char *name)
{
	MonoDomain *current;
	MonoAssembly *ass;
	GSList *tmp;

	mono_domain_assemblies_lock (domain);
	for (tmp = domain->domain_assemblies; tmp; tmp = tmp->next) {
		ass = (MonoAssembly *)tmp->data;
		if (strcmp (name, ass->aname.name) == 0) {
			mono_domain_assemblies_unlock (domain);
			return ass;
		}
	}
	mono_domain_assemblies_unlock (domain);

	if (domain != mono_domain_get ()) {
		current = mono_domain_get ();

		mono_domain_set (domain, FALSE);
		ass = mono_assembly_open (name, NULL);
		mono_domain_set (current, FALSE);
	} else {
		ass = mono_assembly_open (name, NULL);
	}

	return ass;
}
