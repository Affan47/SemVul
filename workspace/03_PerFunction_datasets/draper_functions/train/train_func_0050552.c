calculate_light_strength(gps *cell_vpos)
{
	int i;
	float xdist;
	float ydist;
	float squared_dist;
	gps cell_rpos;
	struct interpolation_data_cell ilights;


	if (!resolve_virtual_position(&cell_rpos, cell_vpos))
		return 0;

	interpolate_light_data(&cell_rpos, &ilights);


	int final_light_strength = max(0, ilights.minimum_light_value);


	light_sources[0].strength = ilights.light_bonus + Me.light_bonus_from_tux;


	for (i = 0; i < MAX_NUMBER_OF_LIGHT_SOURCES; i++) {


		if (light_sources[i].strength == 0)
			break;

		float absolute_intensity = ilights.minimum_light_value + light_sources[i].strength;


		if ( absolute_intensity - final_light_strength < 0 )
			continue;


		xdist = light_sources[i].vpos.x - cell_vpos->x;
		ydist = light_sources[i].vpos.y - cell_vpos->y;
		squared_dist = xdist * xdist + ydist * ydist;


		if ((squared_dist * 4.0 * 4.0) >=
		    (absolute_intensity - final_light_strength) * (absolute_intensity - final_light_strength))
			continue;


		if (squared_dist > (0.5*0.5)) {
			if (!DirectLineColldet(light_sources[i].vpos.x, light_sources[i].vpos.y, cell_vpos->x, cell_vpos->y, cell_vpos->z, &VisiblePassFilter))
				continue;
		}


		final_light_strength = absolute_intensity - 4.0 * sqrt(squared_dist);


		if (final_light_strength >= (NUMBER_OF_SHADOW_IMAGES - 1))
			return (NUMBER_OF_SHADOW_IMAGES - 1);
	}

	return (final_light_strength);

}
