mono_gchandle_get_target (guint32 gchandle)
{
	guint slot = MONO_GC_HANDLE_SLOT (gchandle);
	guint type = MONO_GC_HANDLE_TYPE (gchandle);
	HandleData *handles = &gc_handles [type];
	MonoObject *obj = NULL;
	if (type >= HANDLE_TYPE_MAX)
		return NULL;

	lock_handles (handles);
	if (slot < handles->size && slot_occupied (handles, slot)) {
		if (MONO_GC_HANDLE_TYPE_IS_WEAK (handles->type)) {
			obj = mono_gc_weak_link_get (&handles->entries [slot]);
		} else {
			obj = (MonoObject *)handles->entries [slot];
		}
	} else {

	}
	unlock_handles (handles);

	return obj;
}
