map_slot_unlocked (CK_SLOT_ID slot, Mapping *mapping)
{
	if (!wrap_mappings)
		return CKR_CRYPTOKI_NOT_INITIALIZED;

	if (slot < PLEX_MAPPING_OFFSET)
		return CKR_SLOT_ID_INVALID;
	slot -= PLEX_MAPPING_OFFSET;

	g_assert (mapping);

	if (slot > n_wrap_mappings) {
		return CKR_SLOT_ID_INVALID;
	} else {
		memcpy (mapping, &wrap_mappings[slot], sizeof (Mapping));
		return CKR_OK;
	}
}
