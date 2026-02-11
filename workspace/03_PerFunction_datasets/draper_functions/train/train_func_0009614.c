hud_config_set_color(int color)
{
	int idx;

	hud_config_record_color(color);

	HUD_init_hud_color_array();


	for(idx=0; idx<NUM_HUD_GAUGES; idx++){
		gr_init_alphacolor(&HUD_config.clr[idx], HC_colors[color].r, HC_colors[color].g, HC_colors[color].b, (HUD_color_alpha+1)*16);
	}
}
