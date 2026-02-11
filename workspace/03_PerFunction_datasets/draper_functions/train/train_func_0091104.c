mono_perfcounter_instance_exists (MonoString *instance, MonoString *category, MonoString *machine)
{
	const CategoryDesc *cdesc;


	cdesc = find_category (category);
	if (!cdesc) {
		SharedCategory *scat;
		scat = find_custom_category (category);
		if (!scat)
			return FALSE;
		if (find_custom_instance (scat, instance))
			return TRUE;
	} else {

	}
	return FALSE;
}
