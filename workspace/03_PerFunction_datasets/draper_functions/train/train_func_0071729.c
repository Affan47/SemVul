custom_get_impl (SharedCategory *cat, MonoString* counter, MonoString* instance, int *type)
{
	SharedCounter *scounter;
	SharedInstance* inst;
	int size;

	scounter = find_custom_counter (cat, counter);
	if (!scounter)
		return NULL;
	*type = simple_type_to_type [scounter->type];
	inst = custom_get_instance (cat, scounter, instance);
	if (!inst)
		return NULL;
	size = sizeof (SharedInstance) + strlen (inst->instance_name);
	size += 7;
	size &= ~7;
	return custom_vtable (scounter, inst, (char*)inst + size + scounter->seq_num * sizeof (guint64));
}
