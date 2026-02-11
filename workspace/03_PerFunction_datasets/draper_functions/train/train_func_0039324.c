mono_type_is_valid_type_in_context_full (MonoType *type, MonoGenericContext *context, gboolean check_gtd)
{
	int i;
	MonoGenericInst *inst;

	switch (type->type) {
	case MONO_TYPE_VAR:
	case MONO_TYPE_MVAR:
		if (!context)
			return FALSE;
		inst = type->type == MONO_TYPE_VAR ? context->class_inst : context->method_inst;
		if (!inst || mono_type_get_generic_param_num (type) >= inst->type_argc)
			return FALSE;
		break;
	case MONO_TYPE_SZARRAY:
		return mono_type_is_valid_type_in_context_full (&type->data.klass->byval_arg, context, check_gtd);
	case MONO_TYPE_ARRAY:
		return mono_type_is_valid_type_in_context_full (&type->data.array->eklass->byval_arg, context, check_gtd);
	case MONO_TYPE_PTR:
		return mono_type_is_valid_type_in_context_full (type->data.type, context, check_gtd);
	case MONO_TYPE_GENERICINST:
		inst = type->data.generic_class->context.class_inst;
		if (!inst->is_open)
			break;
		for (i = 0; i < inst->type_argc; ++i)
			if (!mono_type_is_valid_type_in_context_full (inst->type_argv [i], context, check_gtd))
				return FALSE;
		break;
	case MONO_TYPE_CLASS:
	case MONO_TYPE_VALUETYPE: {
		MonoClass *klass = type->data.klass;


		if (klass->byval_arg.type != type->type)
			return mono_type_is_valid_type_in_context_full (&klass->byval_arg, context, check_gtd);

		if (check_gtd && klass->generic_container)
			return FALSE;
		break;
	}
	default:
		break;
	}
	return TRUE;
}
