mono_method_is_generic_sharable_full (MonoMethod *method, gboolean allow_type_vars,
										   gboolean allow_partial, gboolean allow_gsharedvt)
{
	if (!mono_method_is_generic_impl (method))
		return FALSE;

	if (!partial_sharing_supported ())
		allow_partial = FALSE;


	if (is_async_state_machine_class (method->klass))
		return FALSE;

	if (allow_gsharedvt && mini_is_gsharedvt_sharable_method (method)) {
		if (is_async_method (method))
			return FALSE;
		return TRUE;
	}

	if (method->is_inflated) {
		MonoMethodInflated *inflated = (MonoMethodInflated*)method;
		MonoGenericContext *context = &inflated->context;

		if (!mono_generic_context_is_sharable_full (context, allow_type_vars, allow_partial))
			return FALSE;

		g_assert (inflated->declaring);

		if (inflated->declaring->is_generic) {
			if (has_constraints (mono_method_get_generic_container (inflated->declaring)))
				return FALSE;
		}
	}

	if (method->klass->generic_class) {
		if (!mono_generic_context_is_sharable_full (&method->klass->generic_class->context, allow_type_vars, allow_partial))
			return FALSE;

		g_assert (method->klass->generic_class->container_class &&
				method->klass->generic_class->container_class->generic_container);

		if (has_constraints (method->klass->generic_class->container_class->generic_container))
			return FALSE;
	}

	if (method->klass->generic_container && !allow_type_vars)
		return FALSE;


	if (is_async_method (method)) {
		if (mini_method_is_open (method))

			return TRUE;
		return FALSE;
	}

	return TRUE;
}
