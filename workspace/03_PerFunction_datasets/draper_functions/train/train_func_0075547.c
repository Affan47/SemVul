mono_get_delegate_invoke (MonoClass *klass)
{
	MonoMethod *im;


	mono_class_setup_methods (klass);
	if (klass->exception_type)
		return NULL;
	im = mono_class_get_method_from_name (klass, "Invoke", -1);
	return im;
}
