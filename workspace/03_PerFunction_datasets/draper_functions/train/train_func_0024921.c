mini_init_gsctx (MonoDomain *domain, MonoMemPool *mp, MonoGenericContext *context, MonoGenericSharingContext *gsctx)
{
	MonoGenericInst *inst;
	int i;

	memset (gsctx, 0, sizeof (MonoGenericSharingContext));

	if (context && context->class_inst) {
		inst = context->class_inst;
		for (i = 0; i < inst->type_argc; ++i) {
			MonoType *type = inst->type_argv [i];

			if (mini_is_gsharedvt_gparam (type))
				gsctx->is_gsharedvt = TRUE;
		}
	}
	if (context && context->method_inst) {
		inst = context->method_inst;

		for (i = 0; i < inst->type_argc; ++i) {
			MonoType *type = inst->type_argv [i];

			if (mini_is_gsharedvt_gparam (type))
				gsctx->is_gsharedvt = TRUE;
		}
	}
}
