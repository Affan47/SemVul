mono_class_from_generic_parameter_internal (MonoGenericParam *param)
{
	MonoImage *image = get_image_for_generic_param (param);
	MonoGenericParamInfo *pinfo = mono_generic_param_info (param);
	MonoClass *klass, *klass2;


	if (pinfo)
		klass = pinfo->pklass;
	else
		klass = get_anon_gparam_class (param, TRUE);

	if (klass)
		return klass;


	klass = make_generic_param_class (param, pinfo);


	mono_memory_barrier ();

	mono_image_lock (image);


	if (pinfo)
		klass2 = pinfo->pklass;
	else
		klass2 = get_anon_gparam_class (param, FALSE);

	if (klass2) {
		klass = klass2;
	} else {

		if (pinfo)
			pinfo->pklass = klass;
		else
			set_anon_gparam_class (param, klass);
	}
	mono_image_unlock (image);


	if (klass2)
		mono_profiler_class_loaded (klass2, MONO_PROFILE_FAILED);
	else
		mono_profiler_class_loaded (klass, MONO_PROFILE_OK);

	return klass;
}
