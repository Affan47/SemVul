popupdead_draw_button_text()
{
	int w,h,i,sx,sy;

	gr_set_color_fast(&Color_bright_blue);

	for ( i=0; i < Popupdead_num_choices; i++ ) {
		gr_get_string_size(&w, &h, Popupdead_button_text[i]);
		sx = Popupdead_region_coords[gr_screen.res][i][0]-w;
		sy = Popupdead_region_coords[gr_screen.res][i][1]+4;
		gr_string(sx, sy, Popupdead_button_text[i]);
	}
}
