hud_config_green_slider()
{
	int idx;
	int pos = HCS_CONV(HC_color_sliders[HCS_GREEN].get_currentItem()) ;


	if(HC_select_all){
		for(idx=0; idx<NUM_HUD_GAUGES; idx++){
			gr_init_alphacolor(&HUD_config.clr[idx], HUD_config.clr[idx].red, pos, HUD_config.clr[idx].blue, HUD_config.clr[idx].alpha);
		}
	}

	else {
		if(HC_gauge_selected < 0){
			return;
		}


		gr_init_alphacolor(&HUD_config.clr[HC_gauge_selected], HUD_config.clr[HC_gauge_selected].red, pos, HUD_config.clr[HC_gauge_selected].blue, HUD_config.clr[HC_gauge_selected].alpha);
	}

	hud_config_recalc_alpha_slider();
}
