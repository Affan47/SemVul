calculate_attrs (GcrKeyRenderer *self)
{
	if (self->pv->attributes)
		return gck_attributes_ref (self->pv->attributes);

	if (GCK_IS_OBJECT_CACHE (self->pv->object))
		return gck_object_cache_get_attributes (GCK_OBJECT_CACHE (self->pv->object));

	return NULL;
}
