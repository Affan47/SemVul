mono_gc_get_managed_allocator (MonoClass *klass, gboolean for_box)
{
#ifdef MANAGED_ALLOCATION

#ifdef HAVE_KW_THREAD
	int tlab_next_offset = -1;
	int tlab_temp_end_offset = -1;
	MONO_THREAD_VAR_OFFSET (tlab_next, tlab_next_offset);
	MONO_THREAD_VAR_OFFSET (tlab_temp_end, tlab_temp_end_offset);

	if (tlab_next_offset == -1 || tlab_temp_end_offset == -1)
		return NULL;
#endif
	if (collect_before_allocs)
		return NULL;
	if (!mono_runtime_has_tls_get ())
		return NULL;
	if (klass->instance_size > tlab_size)
		return NULL;

	if (klass->has_finalize || mono_class_is_marshalbyref (klass) || (mono_profiler_get_events () & MONO_PROFILE_ALLOCATIONS))
		return NULL;
	if (klass->rank)
		return NULL;
	if (klass->byval_arg.type == MONO_TYPE_STRING)
		return mono_gc_get_managed_allocator_by_type (ATYPE_STRING);

	if (ALIGN_TO (klass->instance_size, ALLOC_ALIGN) < MAX_SMALL_OBJ_SIZE && !mono_class_is_open_constructed_type (&klass->byval_arg))
		return mono_gc_get_managed_allocator_by_type (ATYPE_SMALL);
	else
		return mono_gc_get_managed_allocator_by_type (ATYPE_NORMAL);
#else
	return NULL;
#endif
}
