plr_import_detail()
{
	bool data_failure = false;

	plr->detail_setting = cfread_int(cfp);
	plr->detail_nebula = cfread_int(cfp);
	plr->detail_distance = cfread_int(cfp);
	plr->detail_hardware_textures = cfread_int(cfp);
	plr->detail_num_debris = cfread_int(cfp);
	plr->detail_num_particles = cfread_int(cfp);
	plr->detail_num_stars = cfread_int(cfp);
	plr->detail_shield_effects = cfread_int(cfp);
	plr->detail_lighting = cfread_int(cfp);
	plr->detail_targetview_model = cfread_int(cfp);
	plr->detail_planets_suns = cfread_int(cfp);
	plr->detail_weapon_extras = cfread_int(cfp);

	if ( (plr->detail_setting < -1) || (plr->detail_setting > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_nebula < 0) || (plr->detail_nebula > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_distance < 0) || (plr->detail_distance > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_hardware_textures < 0) || (plr->detail_hardware_textures > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_num_debris < 0) || (plr->detail_num_debris > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_num_particles < 0) || (plr->detail_num_particles > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_num_stars < 0) || (plr->detail_num_stars > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_shield_effects < 0) || (plr->detail_shield_effects > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_lighting < 0) || (plr->detail_lighting > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_targetview_model < 0) || (plr->detail_targetview_model > 1) ) {
		data_failure = true;
	} else 	if ( (plr->detail_planets_suns < 0) || (plr->detail_planets_suns > 1) ) {
		data_failure = true;
	} else 	if ( (plr->detail_weapon_extras < 0) || (plr->detail_weapon_extras > 1) ) {
		data_failure = true;
	}

	if (data_failure) {
		throw "Data check failure in details!";
	}
}
