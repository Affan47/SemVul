mono_metadata_generic_context_hash (const MonoGenericContext *context)
{

	guint hash = 0xc01dfee7;
	if (context->class_inst)
		hash = ((hash << 5) - hash) ^ mono_metadata_generic_inst_hash (context->class_inst);
	if (context->method_inst)
		hash = ((hash << 5) - hash) ^ mono_metadata_generic_inst_hash (context->method_inst);
	return hash;
}
