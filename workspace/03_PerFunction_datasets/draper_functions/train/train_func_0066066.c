renderString(int x, int y, int gauge_id, char *str)
{
	int nx = 0, ny = 0;

	if ( gr_screen.rendering_to_texture != -1 ) {
		gr_set_screen_scale(canvas_w, canvas_h, target_w, target_h);
	} else {
		if ( reticle_follow ) {
			nx = HUD_nose_x;
			ny = HUD_nose_y;

			gr_resize_screen_pos(&nx, &ny);
			gr_set_screen_scale(base_w, base_h);
			gr_unsize_screen_pos(&nx, &ny);
		} else {
			gr_set_screen_scale(base_w, base_h);
		}
	}

	if ( gauge_id > -2 ) {
		emp_hud_string(x + nx, y + ny, gauge_id, str, true);
	} else {
		gr_string(x + nx, y + ny, str);
	}

	gr_reset_screen_scale();
}
