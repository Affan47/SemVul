ves_icall_MonoField_ResolveType (MonoReflectionField *ref_field)
{
	MonoError error;
	MonoClassField *field = ref_field->field;
	MonoType *type = mono_field_get_type_checked (field, &error);
	if (!mono_error_ok (&error))
		mono_error_raise_exception (&error);
	return mono_type_get_object (mono_object_domain (ref_field), type);
}
