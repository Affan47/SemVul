ves_icall_ModuleBuilder_getMethodToken (MonoReflectionModuleBuilder *mb,
					MonoReflectionMethod *method,
					MonoArray *opt_param_types)
{
	MONO_CHECK_ARG_NULL (method, 0);

	return mono_image_create_method_token (
		mb->dynamic_image, (MonoObject *) method, opt_param_types);
}
