hud_show_mini_ship_integrity(object *objp, int x_force, int y_force)
{
	char	text_integrity[64];
	int	numeric_integrity;
	float p_target_integrity;
	int	final_pos[2];

	p_target_integrity = get_hull_pct(objp);

	numeric_integrity = fl2i(p_target_integrity*100 + 0.5f);
	if(numeric_integrity > 100){
		numeric_integrity = 100;
	}


	if ( numeric_integrity == 100 ) {
		final_pos[0] = x_force + Hud_mini_3digit[gr_screen.res][0] - Shield_mini_coords[gr_screen.res][0];
		final_pos[1] = y_force + Hud_mini_3digit[gr_screen.res][1] - Shield_mini_coords[gr_screen.res][1];
	}

	else if ( numeric_integrity < 10 ) {
		final_pos[0] = x_force + Hud_mini_1digit[gr_screen.res][0] - Shield_mini_coords[gr_screen.res][0];
		final_pos[1] = y_force + Hud_mini_1digit[gr_screen.res][1] - Shield_mini_coords[gr_screen.res][1];
	}

	else {
		final_pos[0] = x_force + Hud_mini_2digit[gr_screen.res][0] - Shield_mini_coords[gr_screen.res][0];
		final_pos[1] = y_force + Hud_mini_2digit[gr_screen.res][1] - Shield_mini_coords[gr_screen.res][1];
	}

	if ( numeric_integrity == 0 ) {
		if ( p_target_integrity > 0 ) {
			numeric_integrity = 1;
		}
	}

	sprintf(text_integrity, "%d", numeric_integrity);
	if ( numeric_integrity < 100 ) {
		hud_num_make_mono(text_integrity);
	}

	gr_string(final_pos[0], final_pos[1], text_integrity);
}
