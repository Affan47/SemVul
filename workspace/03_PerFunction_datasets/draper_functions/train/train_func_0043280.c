mono_metadata_is_type_builder_generic_type_definition (MonoClass *container_class, MonoGenericInst *inst, gboolean is_dynamic)
{
	MonoGenericContainer *container = container_class->generic_container;

	if (!is_dynamic || container_class->wastypebuilder || container->type_argc != inst->type_argc)
		return FALSE;
	return inst == container->context.class_inst;
}
