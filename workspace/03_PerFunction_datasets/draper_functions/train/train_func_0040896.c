multi_pxo_pinfo_blit()
{
	int idx;
	int y_start;


	y_start = Multi_pxo_pinfo_coords[gr_screen.res][1];
	for(idx=0; idx<MULTI_PXO_PINFO_NUM_LABELS; idx++){

		gr_set_color_fast(&Color_bright);
		gr_string(Multi_pxo_pinfo_coords[gr_screen.res][0], y_start, Multi_pxo_pinfo_stats_labels[idx]);


		gr_set_color_fast(&Color_normal);
		gr_string(Multi_pxo_pinfo_val_x[gr_screen.res], y_start, Multi_pxo_pinfo_vals[idx]);


		y_start += Multi_pxo_pinfo_stats_spacing[idx];
	}
}
