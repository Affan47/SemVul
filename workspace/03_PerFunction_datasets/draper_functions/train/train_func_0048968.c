detect_area()
{
	if( !mouse.press_area( image_x1,image_y1,image_x2,image_y2, 2 ) &&
		 !mouse.any_click( image_x1,image_y1,image_x2,image_y2, 2 ) )
	{
		return 0;
	}

	int rc = 0;

	int lastXLoc = cur_x_loc;
	int lastYLoc = cur_y_loc;


	if( mouse.single_click( image_x1,image_y1,image_x2,image_y2 ) ||
		 mouse.press_area( image_x1,image_y1,image_x2,image_y2, LEFT_BUTTON ) )
	{
		int xLoc = top_x_loc + (mouse.cur_x-image_x1)/loc_width;
		int yLoc = top_y_loc + (mouse.cur_y-image_y1)/loc_height;


		cur_x_loc = xLoc - world.zoom_matrix->disp_x_loc/2;
		cur_y_loc = yLoc - world.zoom_matrix->disp_y_loc/2;

		if( !valid_cur_box() )
			disp();

		rc=1;
	}


	if( cur_x_loc != lastXLoc || cur_y_loc != lastYLoc )
	{
		world.zoom_matrix->top_x_loc = cur_x_loc;
		world.zoom_matrix->top_y_loc = cur_y_loc;

		sys.zoom_need_redraw = 1;
	}

	return rc;
}
