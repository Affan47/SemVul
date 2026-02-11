ves_icall_System_Array_GetLowerBound (MonoArray *arr, gint32 dimension)
{
	gint32 rank = arr->obj.vtable->klass->rank;

	if ((dimension < 0) || (dimension >= rank)) {
		mono_set_pending_exception (mono_get_exception_index_out_of_range ());
		return 0;
	}

	if (arr->bounds == NULL)
		return 0;

	return arr->bounds [dimension].lower_bound;
}
