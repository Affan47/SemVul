hud_escort_cull_list()
{
	int i;

	int np_index;


	if(MULTI_DOGFIGHT){
		for ( i = 0; i < Num_escort_ships; i++ ) {
			np_index = find_player_id(Escort_ships[i].np_id);


			if ( np_index < 0 ) {
				hud_setup_escort_list(0);
				break;
			}
		}
	}

	else {
		for ( i = 0; i < Num_escort_ships; i++ ) {
			int objnum = Escort_ships[i].objnum;
			Assert( objnum >=0 && objnum < MAX_OBJECTS );

			if ( Objects[objnum].flags & OF_SHOULD_BE_DEAD ) {
				hud_setup_escort_list(0);
				break;
			} else if ( Objects[objnum].type == OBJ_SHIP ) {
				int shipnum = Objects[objnum].instance;
				Assert( shipnum >= 0 && shipnum < MAX_SHIPS );

				if ( (Ships[shipnum].flags & SF_HIDDEN_FROM_SENSORS)
					|| ((Ships[shipnum].flags2 & SF2_STEALTH) && ((Ships[shipnum].team != Player_ship->team) || (Ships[shipnum].flags2 & SF2_FRIENDLY_STEALTH_INVIS)))
				) {
					hud_setup_escort_list(0);
					break;
				}
			}
		}
	}
}
