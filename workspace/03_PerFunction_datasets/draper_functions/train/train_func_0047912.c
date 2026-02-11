GUI_GetEntry(gn_memory_type type, gint nr)
{
	if (nr < 1) return NULL;

	switch (type) {
		case GN_MT_ME:
			if (nr >= memoryStatus.MaxME) return NULL;
			break;
		case GN_MT_SM:
			if (nr >= memoryStatus.MaxSM) return NULL;
			nr += memoryStatus.MaxME;
			break;
		default:
			return NULL;
	}

	if (nr >= contactsMemory->len) return NULL;
	return g_ptr_array_index(contactsMemory, nr - 1);
}
