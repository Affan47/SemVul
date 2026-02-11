hud_abort_lock()
{
	int target_team;

	target_team = obj_team(&Objects[Player_ai->target_objnum]);

	if ( Player_ship->weapons.num_secondary_banks <= 0 ) {
		return 1;
	}

	if ( Player_ship->weapons.current_secondary_bank < 0 ) {
		return 1;
	}


	if ( !ship_secondary_bank_has_ammo(Player_obj->instance) ) {
		return 1;
	}


	if ((Player_ship->team == target_team) && (!iff_x_attacks_y(Player_ship->team, target_team)))
	{

		if(!MULTI_DOGFIGHT) {
			return 1;
		}
	}

	return 0;
}
