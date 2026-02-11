player_generate_killer_weapon_name(int weapon_info_index, int killer_species, char *weapon_name)
{
	if ( weapon_info_index < 0 ) {
		return;
	}

#ifndef NDEBUG
	if ( Show_killer_weapon || (killer_species == Ship_info[Player_ship->ship_info_index].species) ) {
#else
	if (killer_species == Ship_info[Player_ship->ship_info_index].species) {
#endif
		strcpy(weapon_name, Weapon_info[weapon_info_index].name);
	} else {
		if ( Weapon_info[weapon_info_index].subtype == WP_MISSILE ) {
			strcpy(weapon_name, XSTR( "missile", 90));
		} else {
			strcpy(weapon_name, XSTR( "laser fire", 91));
		}
	}
}
