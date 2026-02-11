foreach_destroy_func (gpointer ptr, ObjAttrs *attrs, GdaAttributesManager *mgr)
{
	if (mgr->for_objects)
		g_object_weak_unref (G_OBJECT (ptr),
				     (GWeakNotify) obj_destroyed_cb, attrs);
	attrs->objects = g_slist_remove (attrs->objects, ptr);
}
