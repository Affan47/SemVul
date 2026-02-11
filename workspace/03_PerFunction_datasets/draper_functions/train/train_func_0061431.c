mono_ptr_class_get (MonoType *type)
{
	MonoClass *result;
	MonoClass *el_class;
	MonoImage *image;
	char *name;

	el_class = mono_class_from_mono_type (type);
	image = el_class->image;

	mono_loader_lock ();

	if (!image->ptr_cache)
		image->ptr_cache = g_hash_table_new (mono_aligned_addr_hash, NULL);

	if ((result = g_hash_table_lookup (image->ptr_cache, el_class))) {
		mono_loader_unlock ();
		return result;
	}
	result = mono_image_alloc0 (image, sizeof (MonoClass));

	classes_size += sizeof (MonoClass);

	result->parent = NULL;
	result->name_space = el_class->name_space;
	name = g_strdup_printf ("%s*", el_class->name);
	result->name = mono_image_strdup (image, name);
	g_free (name);

	mono_profiler_class_event (result, MONO_PROFILE_START_LOAD);

	result->image = el_class->image;
	result->inited = TRUE;
	result->flags = TYPE_ATTRIBUTE_CLASS | (el_class->flags & TYPE_ATTRIBUTE_VISIBILITY_MASK);

	result->instance_size = sizeof (gpointer);
	result->cast_class = result->element_class = el_class;
	result->blittable = TRUE;

	result->this_arg.type = result->byval_arg.type = MONO_TYPE_PTR;
	result->this_arg.data.type = result->byval_arg.data.type = &result->element_class->byval_arg;
	result->this_arg.byref = TRUE;

	mono_class_setup_supertypes (result);

	g_hash_table_insert (image->ptr_cache, el_class, result);

	mono_loader_unlock ();

	mono_profiler_class_loaded (result, MONO_PROFILE_OK);

	return result;
}
