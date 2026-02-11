unregister_vtable_reflection_type (MonoVTable *vtable)
{
	MonoObject *type = vtable->type;

	if (type->vtable->klass != mono_defaults.monotype_class)
		MONO_GC_UNREGISTER_ROOT_IF_MOVING (vtable->type);
}
