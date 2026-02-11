techroom_lists_reset()
{
	int i;


	if(Tab != SHIPS_DATA_TAB)
		techroom_unload_animation();

	Current_list = NULL;
	Current_list_size = 0;

	model_free_all();

	if (Ship_list != NULL) {
		delete[] Ship_list;
		Ship_list = NULL;
	}

	Ship_list_size = 0;
	Ships_loaded = 0;

	if (Weapon_list != NULL) {
		for (i = 0; i < Weapon_list_size; i++) {
			if (Weapon_list[i].animation.num_frames != 0) {
				generic_anim_unload(&Weapon_list[i].animation);
			}

			if (Weapon_list[i].bitmap >= 0) {
				bm_release(Weapon_list[i].bitmap);
				Weapon_list[i].bitmap = -1;
			}
		}

		delete[] Weapon_list;
		Weapon_list = NULL;
	}

	Weapon_list_size = 0;
	Weapons_loaded = 0;

	for (i = 0; i < Intel_list_size; i++) {
		if (Intel_list[i].animation.num_frames != 0) {
			generic_anim_unload(&Intel_list[i].animation);
		}

		if (Intel_list[i].bitmap >= 0) {
			bm_release(Intel_list[i].bitmap);
			Intel_list[i].bitmap = -1;
		}
	}

	Intel_list_size = 0;
	Intel_loaded = 0;
}
