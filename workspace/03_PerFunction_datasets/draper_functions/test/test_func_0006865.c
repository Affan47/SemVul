mono_method_check_context_used (MonoMethod *method)
{
	MonoGenericContext *method_context = mini_method_get_context (method);
	int context_used = 0;

	if (!method_context) {

		if (method->klass->rank)
			context_used = mono_class_check_context_used (method->klass);
	} else {
		context_used = mono_generic_context_check_used (method_context);
		context_used |= mono_class_check_context_used (method->klass);
	}

	return context_used;
}
