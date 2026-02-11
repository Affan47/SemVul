sgen_is_bridge_object (MonoObject *obj)
{
	if ((obj->vtable->gc_bits & SGEN_GC_BIT_BRIDGE_OBJECT) != SGEN_GC_BIT_BRIDGE_OBJECT)
		return FALSE;
	return bridge_callbacks.is_bridge_object (obj);
}
