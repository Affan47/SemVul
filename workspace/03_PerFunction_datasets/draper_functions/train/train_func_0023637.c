mono_class_get_inflated_method (MonoClass *klass, MonoMethod *method)
{
	MonoClass *gklass = klass->generic_class->container_class;
	int i;

	g_assert (method->klass == gklass);

	mono_class_setup_methods (gklass);
	g_assert (!gklass->exception_type);

	for (i = 0; i < gklass->method.count; ++i) {
		if (gklass->methods [i] == method) {
			if (klass->methods) {
				return klass->methods [i];
			} else {
				MonoError error;
				MonoMethod *result = mono_class_inflate_generic_method_full_checked (gklass->methods [i], klass, mono_class_get_context (klass), &error);
				g_assert (mono_error_ok (&error));
				return result;
			}
		}
	}

	return NULL;
}
