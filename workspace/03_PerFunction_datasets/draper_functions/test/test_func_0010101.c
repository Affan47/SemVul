hud_config_alpha_slider_up()
{
	int pos = HCS_CONV(HC_color_sliders[HCS_ALPHA].get_currentItem());
	int max = MAX(MAX( HCS_CONV(HC_color_sliders[HCS_RED].get_currentItem()), HCS_CONV(HC_color_sliders[HCS_GREEN].get_currentItem()) ), HCS_CONV(HC_color_sliders[HCS_BLUE].get_currentItem()) );


	if(max >= 255){
		HC_color_sliders[HCS_ALPHA].force_currentItem( HCS_CONV(pos - 1) );
		return;
	}


	HC_color_sliders[HCS_RED].force_currentItem( HCS_CONV(HCS_CONV(HC_color_sliders[HCS_RED].get_currentItem()) + 1) );
	HC_color_sliders[HCS_GREEN].force_currentItem( HCS_CONV(HCS_CONV(HC_color_sliders[HCS_GREEN].get_currentItem()) + 1) );
	HC_color_sliders[HCS_BLUE].force_currentItem( HCS_CONV(HCS_CONV(HC_color_sliders[HCS_BLUE].get_currentItem()) + 1) );


	if(HC_select_all){
		hud_config_stuff_colors( HCS_CONV(HC_color_sliders[HCS_RED].get_currentItem()), HCS_CONV(HC_color_sliders[HCS_GREEN].get_currentItem()), HCS_CONV(HC_color_sliders[HCS_BLUE].get_currentItem()) );
	} else {
		gr_init_alphacolor(&HUD_config.clr[HC_gauge_selected], HCS_CONV(HC_color_sliders[HCS_RED].get_currentItem()), HCS_CONV(HC_color_sliders[HCS_GREEN].get_currentItem()), HCS_CONV(HC_color_sliders[HCS_BLUE].get_currentItem()), 255);
	}
}
