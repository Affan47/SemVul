custom_attrs_get_by_type (MonoObject *obj, MonoReflectionType *attr_type)
{
	MonoClass *attr_class = attr_type ? mono_class_from_mono_type (attr_type->type) : NULL;
	MonoArray *res;
	MonoError error;

	if (attr_class)
		mono_class_init_or_throw (attr_class);

	res = mono_reflection_get_custom_attrs_by_type (obj, attr_class, &error);
	mono_error_raise_exception (&error);

	if (mono_loader_get_last_error ()) {
		mono_set_pending_exception (mono_loader_error_prepare_exception (mono_loader_get_last_error ()));
		return NULL;
	} else {
		return res;
	}
}
