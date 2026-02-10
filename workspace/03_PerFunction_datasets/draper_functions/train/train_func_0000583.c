check_field_access (MonoMethod *caller, MonoClassField *field)
{

	if (caller) {
		MonoError error;
		MonoClass *klass;


		mono_field_get_type_checked (field, &error);
		if (!mono_error_ok (&error)) {
			mono_error_cleanup (&error);
			return FALSE;
		}

		klass = (mono_field_get_flags (field) & FIELD_ATTRIBUTE_STATIC) ? NULL : mono_field_get_parent (field);
		return mono_method_can_access_field_full (caller, field, klass);
	}
	return FALSE;
}
