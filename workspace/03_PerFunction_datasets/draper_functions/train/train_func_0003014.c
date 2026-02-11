hud_config_check_regions()
{
	int			i;
	UI_BUTTON	*b;

	for ( i=0; i<NUM_HUD_GAUGES; i++ ) {
		b = &HC_gauge_regions[gr_screen.res][i].button;


		if ( b->button_hilighted() ) {
			HC_gauge_hot = i;
		}

		if ( b->pressed() ) {
			gamesnd_play_iface(SND_USER_SELECT);
			HC_gauge_selected = i;


			hud_config_select_all_toggle(0);


			if(HC_gauge_regions[gr_screen.res][i].use_iff){
				HC_color_sliders[HCS_RED].hide();
				HC_color_sliders[HCS_GREEN].hide();
				HC_color_sliders[HCS_BLUE].hide();
				HC_color_sliders[HCS_ALPHA].hide();

				HC_color_sliders[HCS_RED].disable();
				HC_color_sliders[HCS_GREEN].disable();
				HC_color_sliders[HCS_BLUE].disable();
				HC_color_sliders[HCS_ALPHA].disable();
			} else {
				HC_color_sliders[HCS_RED].enable();
				HC_color_sliders[HCS_GREEN].enable();
				HC_color_sliders[HCS_BLUE].enable();
				HC_color_sliders[HCS_ALPHA].enable();

				HC_color_sliders[HCS_RED].unhide();
				HC_color_sliders[HCS_GREEN].unhide();
				HC_color_sliders[HCS_BLUE].unhide();
				HC_color_sliders[HCS_ALPHA].unhide();

				HC_color_sliders[HCS_RED].force_currentItem( HCS_CONV(HUD_config.clr[i].red) );
				HC_color_sliders[HCS_GREEN].force_currentItem( HCS_CONV(HUD_config.clr[i].green) );
				HC_color_sliders[HCS_BLUE].force_currentItem( HCS_CONV(HUD_config.clr[i].blue) );
				HC_color_sliders[HCS_ALPHA].force_currentItem( HCS_CONV(HUD_config.clr[i].alpha) );
			}


			hud_config_recalc_alpha_slider();
		}
	}
}
