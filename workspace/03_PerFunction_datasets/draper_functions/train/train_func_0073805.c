set_default_recharge_rates(object* obj)
{
	int ship_properties;

	ship* ship_p = &Ships[obj->instance];
	ship_info* ship_info_p = &Ship_info[ship_p->ship_info_index];

	if ( ship_info_p->power_output == 0 )
		return;

	ship_properties = 0;
	if (ship_has_energy_weapons(ship_p))
		ship_properties |= HAS_WEAPONS;

	if (!(obj->flags & OF_NO_SHIELDS))
		ship_properties |= HAS_SHIELDS;

	if (ship_has_engine_power(ship_p))
		ship_properties |= HAS_ENGINES;


	switch ( ship_properties ) {
		case HAS_ENGINES | HAS_WEAPONS | HAS_SHIELDS:
			ship_p->shield_recharge_index = INTIAL_SHIELD_RECHARGE_INDEX;
			ship_p->weapon_recharge_index = INTIAL_WEAPON_RECHARGE_INDEX;
			ship_p->engine_recharge_index = INTIAL_ENGINE_RECHARGE_INDEX;
			break;

		case HAS_ENGINES | HAS_SHIELDS:
			ship_p->shield_recharge_index = ONE_HALF_INDEX;
			ship_p->weapon_recharge_index = ZERO_INDEX;
			ship_p->engine_recharge_index = ONE_HALF_INDEX;
			break;

		case HAS_WEAPONS | HAS_SHIELDS:
			ship_p->shield_recharge_index = ONE_HALF_INDEX;
			ship_p->weapon_recharge_index = ONE_HALF_INDEX;
			ship_p->engine_recharge_index = ZERO_INDEX;
			break;

		case HAS_ENGINES | HAS_WEAPONS:
			ship_p->shield_recharge_index = ZERO_INDEX;
			ship_p->weapon_recharge_index = ONE_HALF_INDEX;
			ship_p->engine_recharge_index = ONE_HALF_INDEX;
			break;

		case HAS_SHIELDS:
			ship_p->shield_recharge_index = ALL_INDEX;
			ship_p->weapon_recharge_index = ZERO_INDEX;
			ship_p->engine_recharge_index = ZERO_INDEX;
			break;

		case HAS_ENGINES:
			ship_p->shield_recharge_index = ZERO_INDEX;
			ship_p->weapon_recharge_index = ZERO_INDEX;
			ship_p->engine_recharge_index = ALL_INDEX;
			break;

		case HAS_WEAPONS:
			ship_p->shield_recharge_index = ZERO_INDEX;
			ship_p->weapon_recharge_index = ALL_INDEX;
			ship_p->engine_recharge_index = ZERO_INDEX;
			break;

		default:
			Int3();
			break;
	}
}
