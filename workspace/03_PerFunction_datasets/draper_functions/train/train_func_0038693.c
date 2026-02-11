ves_icall_System_Runtime_InteropServices_Marshal_ReAllocHGlobal (gpointer ptr, gpointer size)
{
	gpointer res;
	size_t s = (size_t)size;

	if (ptr == NULL) {
		mono_gc_out_of_memory (s);
		return NULL;
	}

#ifdef HOST_WIN32
	res = GlobalReAlloc (ptr, s, GMEM_MOVEABLE);
#else
	res = g_try_realloc (ptr, s);
#endif
	if (!res)
		mono_gc_out_of_memory (s);

	return res;
}
