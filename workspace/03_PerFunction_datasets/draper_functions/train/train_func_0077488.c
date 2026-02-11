deregister_reflection_info_roots (MonoDomain *domain)
{
	GSList *list;

	mono_domain_assemblies_lock (domain);
	for (list = domain->domain_assemblies; list; list = list->next) {
		MonoAssembly *assembly = list->data;
		MonoImage *image = assembly->image;
		int i;


		if (image->dynamic)
			deregister_reflection_info_roots_from_list (image);

		for (i = 0; i < image->module_count; ++i) {
			MonoImage *module = image->modules [i];
			if (module && module->dynamic)
				deregister_reflection_info_roots_from_list (module);
		}
	}
	mono_domain_assemblies_unlock (domain);
}
