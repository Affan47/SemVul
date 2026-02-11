mono_class_get_method_from_name_flags (MonoClass *klass, const char *name, int param_count, int flags)
{
	MonoMethod *res = NULL;
	int i;

	mono_class_init (klass);

	if (klass->generic_class && !klass->methods) {
		res = mono_class_get_method_from_name_flags (klass->generic_class->container_class, name, param_count, flags);
		if (res) {
			MonoError error;
			res = mono_class_inflate_generic_method_full_checked (res, klass, mono_class_get_context (klass), &error);
			if (!mono_error_ok (&error))
				mono_error_cleanup (&error);
		}
		return res;
	}

	if (klass->methods || !MONO_CLASS_HAS_STATIC_METADATA (klass)) {
		mono_class_setup_methods (klass);


		if (!klass->methods)
			return NULL;
		for (i = 0; i < klass->method.count; ++i) {
			MonoMethod *method = klass->methods [i];

			if (method->name[0] == name [0] &&
				!strcmp (name, method->name) &&
				(param_count == -1 || mono_method_signature (method)->param_count == param_count) &&
				((method->flags & flags) == flags)) {
				res = method;
				break;
			}
		}
	}
	else {
	    res = find_method_in_metadata (klass, name, param_count, flags);
	}

	return res;
}
