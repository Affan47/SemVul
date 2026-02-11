hud_shield_level_init()
{
	unsigned int i;
	hud_frames temp;

	hud_shield_hit_reset(1);

	if ( !Hud_shield_inited ) {
		for ( i = 0; i < Hud_shield_filenames.size(); i++ ) {
			Shield_gauges.push_back(temp);
			Shield_gauges.at(i).first_frame = -1;
			Shield_gauges.at(i).num_frames  = 0;
		}

		Hud_shield_inited = 1;
	}

	Shield_mini_gauge.first_frame = bm_load_animation("targhit1", &Shield_mini_gauge.num_frames);
	if ( Shield_mini_gauge.first_frame == -1 ) {
		Warning(LOCATION, "Could not load in the HUD shield ani: targethit1\n");
		return;
	}
	Shield_mini_loaded = 1;
}
