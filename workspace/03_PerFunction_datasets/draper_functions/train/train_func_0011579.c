mono_gchandle_free (guint32 gchandle)
{
	guint slot = gchandle >> 3;
	guint type = (gchandle & 7) - 1;
	HandleData *handles = &gc_handles [type];
	if (type > 3)
		return;

	lock_handles (handles);
	if (slot < handles->size && (handles->bitmap [slot / 32] & (1 << (slot % 32)))) {
		if (handles->type <= HANDLE_WEAK_TRACK) {
			if (handles->entries [slot])
				mono_gc_weak_link_remove (&handles->entries [slot], handles->type == HANDLE_WEAK_TRACK);
		} else {
			handles->entries [slot] = NULL;
		}
		handles->bitmap [slot / 32] &= ~(1 << (slot % 32));
	} else {

	}
#ifndef DISABLE_PERFCOUNTERS
	mono_perfcounters->gc_num_handles--;
#endif

	unlock_handles (handles);
	mono_profiler_gc_handle (MONO_PROFILER_GC_HANDLE_DESTROYED, handles->type, gchandle, NULL);
}
