wield_slot_ammo(const object_type *o_ptr)
{
	s16b i, open = 0;


	i = get_inscribed_ammo_slot(o_ptr);
	if (i && !inventory[i].k_idx) return i;

	for (i = QUIVER_START; i < QUIVER_END; i++)
	{
		if (!inventory[i].k_idx)
		{

			if (!open) open = i;
			continue;
		}


		if (cursed_p(&inventory[i])) continue;


		if (object_similar(&inventory[i], o_ptr)) return i;
	}


	return open ? open : QUIVER_START;
}
