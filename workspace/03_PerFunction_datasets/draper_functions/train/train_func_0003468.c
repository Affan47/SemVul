radar_mission_init()
{
	for (int i=0; i<MAX_RADAR_COLORS; i++ )	{
		for (int j=0; j<MAX_RADAR_LEVELS; j++ )	{
			if (radar_iff_color[i][j][0] >= 0) {
				gr_init_alphacolor( &Radar_colors[i][j], radar_iff_color[i][j][0], radar_iff_color[i][j][1], radar_iff_color[i][j][2], radar_iff_color[i][j][3] );
			} else {
				gr_init_alphacolor( &Radar_colors[i][j], Radar_color_rgb[i][j].r, Radar_color_rgb[i][j].g, Radar_color_rgb[i][j].b, 255 );
			}
		}
	}

	Radar_calc_bright_dist_timer = timestamp(0);
}
