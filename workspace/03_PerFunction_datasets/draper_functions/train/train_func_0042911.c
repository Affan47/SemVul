labviewer_change_bitmap(int ship_index = -1, int weapon_index = -1)
{
	if ( (ship_index < 0) && (weapon_index < 0) ) {
		if (Lab_bitmap_id >= 0) {
			bm_release(Lab_bitmap_id);
			Lab_bitmap_id = -1;
		}

		return;
	}

	if ( !Lab_in_mission ) {
		if (ship_index >= 0) {

		} else if (weapon_index >= 0) {

			extern void weapon_load_bitmaps(int);
			weapon_load_bitmaps(weapon_index);
			Lab_bitmap_id = Weapon_info[weapon_index].laser_bitmap.first_frame;
		}
	}

	if (Lab_bitmap_id >= 0) {
		bm_get_filename(Lab_bitmap_id, Lab_bitmap_filename);
	} else {
		memset( Lab_bitmap_filename, 0, sizeof(Lab_bitmap_filename) );
	}

	labviewer_update_flags_window();
}
