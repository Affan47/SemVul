map_slot_to_real (CK_SLOT_ID_PTR slot, Mapping *mapping)
{
	CK_RV rv;

	g_assert (mapping);

	G_LOCK (wrap_layer);

		rv = map_slot_unlocked (*slot, mapping);
		if (rv == CKR_OK)
			*slot = mapping->real_slot;

	G_UNLOCK (wrap_layer);

	return rv;
}
