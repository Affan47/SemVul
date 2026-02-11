wl_update_parse_object_weapons(p_object *pobjp, wss_unit *slot)
{
	int				i,	j, sidx, pilot_index, max_count;
	subsys_status	*ss;

	Assert(slot->ship_class >= 0);

	pilot_index = wl_get_pilot_subsys_index(pobjp);

	if ( pilot_index == -1 )
		return;

	ss = &Subsys_status[pilot_index];

	for ( i = 0; i < MAX_SHIP_PRIMARY_BANKS; i++ ) {
		ss->primary_banks[i] = -1;
	}

	for ( i = 0; i < MAX_SHIP_SECONDARY_BANKS; i++ ) {
		ss->secondary_banks[i] = -1;
	}

	j = 0;
	for ( i = 0; i < MAX_SHIP_PRIMARY_BANKS; i++ )
	{
		if ( (slot->wep_count[i] > 0) && (slot->wep[i] >= 0) )
		{
			ss->primary_banks[j] = slot->wep[i];


			if (Weapon_info[slot->wep[i]].wi_flags2 & WIF2_BALLISTIC)
			{


				ss->primary_ammo[j] = 100;
			}
			else
			{
				ss->primary_ammo[j] = 0;
			}

			j++;
		}
	}

	j = 0;
	for ( i = 0; i < MAX_SHIP_SECONDARY_BANKS; i++ )
	{
		sidx = i+MAX_SHIP_PRIMARY_BANKS;
		if ( (slot->wep_count[sidx] > 0) && (slot->wep[sidx] >= 0) )
		{
			ss->secondary_banks[j] = slot->wep[sidx];


			max_count = wl_calc_missile_fit(slot->wep[sidx], Ship_info[slot->ship_class].secondary_bank_ammo_capacity[j]);
			ss->secondary_ammo[j] = fl2i( i2fl(slot->wep_count[sidx]) / max_count * 100.0f + 0.5f);

			j++;
		}
	}
}
