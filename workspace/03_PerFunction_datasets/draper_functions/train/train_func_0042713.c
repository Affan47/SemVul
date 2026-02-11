get_from_turn_permission_hashtable(turn_permission_hashtable *map, const ioa_addr *addr)
{
	if (!addr || !map)
		return NULL;

	u32bits index = addr_hash_no_port(addr) & (TURN_PERMISSION_HASHTABLE_SIZE-1);
	turn_permission_array *parray = &(map->table[index]);

	{
		size_t i;
		for (i = 0; i < TURN_PERMISSION_ARRAY_SIZE; ++i) {
			turn_permission_slot *slot = &(parray->main_slots[i]);
			if (slot->info.allocated && addr_eq_no_port(&(slot->info.addr), addr)) {
				return &(slot->info);
			}
		}
	}

	if(parray->extra_slots) {

		size_t i;
		size_t sz = parray->extra_sz;
		for (i = 0; i < sz; ++i) {
			turn_permission_slot *slot = parray->extra_slots[i];
			if (slot->info.allocated && addr_eq_no_port(&(slot->info.addr), addr)) {
				return &(slot->info);
			}
		}
	}

	return NULL;
}
