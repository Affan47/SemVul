handle_data_first_unset (HandleData *handles)
{
	gint slot;
	for (slot = 0; slot < handles->slot_hint; ++slot) {
		if (handles->bitmap [slot] == 0xffffffff)
			continue;
		handles->slot_hint = slot;
		return find_first_unset (handles->bitmap [slot]);
	}
	return -1;
}
