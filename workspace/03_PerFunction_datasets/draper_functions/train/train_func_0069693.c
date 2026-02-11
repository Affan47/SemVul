tux_wants_to_attack_now(int use_mouse_cursor_for_targeting)
{


	if (Me.busy_time > 0) {
		return;
	}


	if (Me.weapon_item.type >= 0) {
		if (ItemMap[Me.weapon_item.type].item_gun_use_ammunition) {
			if (Me.weapon_item.ammo_clip <= 0) {
				No_Ammo_Sound();


				append_new_game_message(_("%s empty, reloading..."),ItemMap[Me.weapon_item.type].item_name);
				TuxReloadWeapon();
				return;

			}
		}
	}

	if (PerformTuxAttackRaw(use_mouse_cursor_for_targeting)) {
		return;
	}

	if (Me.weapon_item.type >= 0)
		DamageWeapon(&(Me.weapon_item));


	if (Me.weapon_item.type >= 0) {
		if (ItemMap[Me.weapon_item.type].item_gun_use_ammunition) {
			Me.weapon_item.ammo_clip--;
		}
	}

}
