object_is_live (GCObject **objp)
{
	GCObject *obj = *objp;
	GCObject *fwd = SGEN_OBJECT_IS_FORWARDED (obj);
	if (fwd) {
		*objp = fwd;
		return sgen_hash_table_lookup (&hash_table, fwd) == NULL;
	}
	if (!sgen_object_is_live (obj))
		return FALSE;
	return sgen_hash_table_lookup (&hash_table, obj) == NULL;
}
