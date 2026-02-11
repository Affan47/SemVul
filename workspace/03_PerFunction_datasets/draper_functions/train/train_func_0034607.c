mono_generic_param_is_constraint_compatible (VerifyContext *ctx, MonoGenericParam *target, MonoGenericParam *candidate, MonoClass *candidate_param_class, MonoGenericContext *context)
{
	MonoGenericParamInfo *tinfo = mono_generic_param_info (target);
	MonoGenericParamInfo *cinfo = mono_generic_param_info (candidate);
	MonoClass **candidate_class;
	gboolean class_constraint_satisfied = FALSE;
	gboolean valuetype_constraint_satisfied = FALSE;

	int tmask = tinfo->flags & GENERIC_PARAMETER_ATTRIBUTE_SPECIAL_CONSTRAINTS_MASK;
	int cmask = cinfo->flags & GENERIC_PARAMETER_ATTRIBUTE_SPECIAL_CONSTRAINTS_MASK;

	if (cinfo->constraints) {
		for (candidate_class = cinfo->constraints; *candidate_class; ++candidate_class) {
			MonoClass *cc;
			MonoType *inflated = verifier_inflate_type (ctx, &(*candidate_class)->byval_arg, ctx->generic_context);
			if (!inflated)
				return FALSE;
			cc = mono_class_from_mono_type (inflated);
			mono_metadata_free_type (inflated);

			if (mono_type_is_reference (&cc->byval_arg) && !MONO_CLASS_IS_INTERFACE (cc))
				class_constraint_satisfied = TRUE;
			else if (!mono_type_is_reference (&cc->byval_arg) && !MONO_CLASS_IS_INTERFACE (cc))
				valuetype_constraint_satisfied = TRUE;
		}
	}
	class_constraint_satisfied |= (cmask & GENERIC_PARAMETER_ATTRIBUTE_REFERENCE_TYPE_CONSTRAINT) != 0;
	valuetype_constraint_satisfied |= (cmask & GENERIC_PARAMETER_ATTRIBUTE_VALUE_TYPE_CONSTRAINT) != 0;

	if ((tmask & GENERIC_PARAMETER_ATTRIBUTE_REFERENCE_TYPE_CONSTRAINT) && !class_constraint_satisfied)
		return FALSE;
	if ((tmask & GENERIC_PARAMETER_ATTRIBUTE_VALUE_TYPE_CONSTRAINT) && !valuetype_constraint_satisfied)
		return FALSE;
	if ((tmask & GENERIC_PARAMETER_ATTRIBUTE_CONSTRUCTOR_CONSTRAINT) && !((cmask & GENERIC_PARAMETER_ATTRIBUTE_CONSTRUCTOR_CONSTRAINT) ||
		valuetype_constraint_satisfied)) {
		return FALSE;
	}


	if (tinfo->constraints) {
		MonoClass **target_class;
		for (target_class = tinfo->constraints; *target_class; ++target_class) {
			MonoClass *tc;
			MonoType *inflated = verifier_inflate_type (ctx, &(*target_class)->byval_arg, context);
			if (!inflated)
				return FALSE;
			tc = mono_class_from_mono_type (inflated);
			mono_metadata_free_type (inflated);


			if (mono_metadata_type_equal (&tc->byval_arg, &candidate_param_class->byval_arg))
				continue;

			if (!cinfo->constraints)
				return FALSE;

			for (candidate_class = cinfo->constraints; *candidate_class; ++candidate_class) {
				MonoClass *cc;
				inflated = verifier_inflate_type (ctx, &(*candidate_class)->byval_arg, ctx->generic_context);
				if (!inflated)
					return FALSE;
				cc = mono_class_from_mono_type (inflated);
				mono_metadata_free_type (inflated);

				if (verifier_class_is_assignable_from (tc, cc))
					break;


				if (mono_type_is_generic_argument (&cc->byval_arg)) {
					MonoGenericParam *other_candidate = verifier_get_generic_param_from_type (ctx, &cc->byval_arg);

					if (mono_generic_param_is_constraint_compatible (ctx, target, other_candidate, cc, context)) {
						break;
					}
				}
			}
			if (!*candidate_class)
				return FALSE;
		}
	}
	return TRUE;
}
