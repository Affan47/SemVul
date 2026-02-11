multi_pxo_com_blit_text()
{

	if(Multi_pxo_com_top_text[0] != '\0'){
		gr_set_color_fast(&Color_bright);
		gr_string(Multi_pxo_com_top_text_coords[gr_screen.res][0], Multi_pxo_com_top_text_coords[gr_screen.res][1], Multi_pxo_com_top_text);
	}
	if(Multi_pxo_com_middle_text[0] != '\0'){
		gr_set_color_fast(&Color_bright);
		gr_string(Multi_pxo_com_top_text_coords[gr_screen.res][0], Multi_pxo_com_middle_text_y[gr_screen.res], Multi_pxo_com_middle_text);
	}
	if(Multi_pxo_com_bottom_text[0] != '\0'){
		gr_set_color_fast(&Color_bright);
		gr_string(Multi_pxo_com_top_text_coords[gr_screen.res][0], Multi_pxo_com_bottom_text_y[gr_screen.res], Multi_pxo_com_bottom_text);
	}
}
