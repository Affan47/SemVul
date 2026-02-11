ves_icall_System_Runtime_CompilerServices_RuntimeHelpers_RunModuleConstructor (MonoImage *image)
{
	MonoError error;

	mono_image_check_for_module_cctor (image);
	if (image->has_module_cctor) {
		MonoClass *module_klass = mono_class_get_checked (image, MONO_TOKEN_TYPE_DEF | 1, &error);
		mono_error_raise_exception (&error);

		mono_runtime_class_init (mono_class_vtable_full (mono_domain_get (), module_klass, TRUE));
	}
}
