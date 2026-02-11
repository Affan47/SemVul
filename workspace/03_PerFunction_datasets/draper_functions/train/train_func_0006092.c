mono_perfcounter_get_impl (MonoString* category, MonoString* counter, MonoString* instance,
		MonoString* machine, int *type, MonoBoolean *custom)
{
	const CategoryDesc *cdesc;

	if (mono_string_compare_ascii (machine, "."))
		return NULL;
	cdesc = find_category (category);
	if (!cdesc) {
		SharedCategory *scat = find_custom_category (category);
		if (!scat)
			return NULL;
		*custom = TRUE;
		return custom_get_impl (scat, counter, instance, type);
	}
	switch (cdesc->id) {
	case CATEGORY_CPU:
		return cpu_get_impl (counter, instance, type, custom);
	case CATEGORY_PROC:
		return process_get_impl (counter, instance, type, custom);
	case CATEGORY_MONO_MEM:
		return mono_mem_get_impl (counter, instance, type, custom);
	case CATEGORY_NETWORK:
		return network_get_impl (counter, instance, type, custom);
	case CATEGORY_JIT:
	case CATEGORY_EXC:
	case CATEGORY_GC:
	case CATEGORY_REMOTING:
	case CATEGORY_LOADING:
	case CATEGORY_THREAD:
	case CATEGORY_INTEROP:
	case CATEGORY_SECURITY:
	case CATEGORY_ASPNET:
	case CATEGORY_THREADPOOL:
		return predef_writable_get_impl (cdesc->id, counter, instance, type, custom);
	}
	return NULL;
}
