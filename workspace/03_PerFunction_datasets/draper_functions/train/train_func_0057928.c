hud_config_set_button_state()
{
	if ( HC_gauge_selected < 0 ) {
		hud_config_button_disable(HCB_ON);
		hud_config_button_disable(HCB_OFF);
		hud_config_button_disable(HCB_POPUP);
		return;
	}


	hud_config_button_enable(HCB_ON);
	hud_config_button_enable(HCB_OFF);


	if ( HC_gauge_regions[gr_screen.res][HC_gauge_selected].can_popup ) {
		hud_config_button_enable(HCB_POPUP);
	} else {
		hud_config_button_disable(HCB_POPUP);
	}
}
