mono_class_is_variant_compatible (MonoClass *klass, MonoClass *oklass, gboolean check_for_reference_conv)
{
	int j;
	MonoType **klass_argv, **oklass_argv;
	MonoClass *klass_gtd = mono_class_get_generic_type_definition (klass);
	MonoGenericContainer *container = klass_gtd->generic_container;

	if (klass == oklass)
		return TRUE;


	if (mono_class_get_generic_type_definition (oklass) != klass_gtd || oklass == klass_gtd)
		return FALSE;

	klass_argv = &klass->generic_class->context.class_inst->type_argv [0];
	oklass_argv = &oklass->generic_class->context.class_inst->type_argv [0];

	for (j = 0; j < container->type_argc; ++j) {
		MonoClass *param1_class = mono_class_from_mono_type (klass_argv [j]);
		MonoClass *param2_class = mono_class_from_mono_type (oklass_argv [j]);

		if (param1_class->valuetype != param2_class->valuetype || (param1_class->valuetype && param1_class != param2_class))
			return FALSE;


		if (param1_class != param2_class) {
			if (mono_generic_container_get_param_info (container, j)->flags & MONO_GEN_PARAM_VARIANT) {
				if (!mono_gparam_is_reference_conversible (param1_class, param2_class, check_for_reference_conv))
					return FALSE;
			} else if (mono_generic_container_get_param_info (container, j)->flags & MONO_GEN_PARAM_COVARIANT) {
				if (!mono_gparam_is_reference_conversible (param2_class, param1_class, check_for_reference_conv))
					return FALSE;
			} else
				return FALSE;
		}
	}
	return TRUE;
}
