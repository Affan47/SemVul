mono_get_method_constrained_with_method (MonoImage *image, MonoMethod *method, MonoClass *constrained_class,
			     MonoGenericContext *context, MonoError *error)
{
	g_assert (method);

	return get_method_constrained (image, method, constrained_class, context, error);
}
