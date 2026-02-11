mono_gc_ephemeron_array_add (MonoObject *obj)
{
	EphemeronLinkNode *node;

	LOCK_GC;

	node = (EphemeronLinkNode *)sgen_alloc_internal (INTERNAL_MEM_EPHEMERON_LINK);
	if (!node) {
		UNLOCK_GC;
		return FALSE;
	}
	node->array = (MonoArray*)obj;
	node->next = ephemeron_list;
	ephemeron_list = node;

	SGEN_LOG (5, "Registered ephemeron array %p", obj);

	UNLOCK_GC;
	return TRUE;
}
