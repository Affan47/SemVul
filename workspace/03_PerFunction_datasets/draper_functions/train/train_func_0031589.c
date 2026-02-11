debug_max_primary_weapons(object *objp)
{
	Assert(objp);

	int index;
	ship *shipp = &Ships[objp->instance];
	ship_info *sip = &Ship_info[shipp->ship_info_index];
	ship_weapon *swp = &shipp->weapons;
	weapon_info *wip;

	if (sip->flags & SIF_BALLISTIC_PRIMARIES)
	{
		for ( index = 0; index < MAX_SHIP_PRIMARY_BANKS; index++ )
		{
			wip = &Weapon_info[swp->primary_bank_weapons[index]];
			if (wip->wi_flags2 & WIF2_BALLISTIC)
			{
				float capacity, size;
				capacity = (float) sip->primary_bank_ammo_capacity[index];
				size = (float) wip->cargo_size;
				swp->primary_bank_ammo[index] = fl2i((capacity / size)+0.5f);
			}
		}
	}
}
