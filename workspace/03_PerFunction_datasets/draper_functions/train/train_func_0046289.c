draw_selected()
{
	Location* locPtr = world.get_loc(map_x_loc, map_y_loc);

	if( locPtr->is_firm() || locPtr->is_town() )
		return;


	int x1 = map_x_loc * ZOOM_LOC_WIDTH;
	int y1 = map_y_loc * ZOOM_LOC_HEIGHT;
	int x2 = x1 + ZOOM_LOC_WIDTH  - 1;
	int y2 = y1 + ZOOM_LOC_HEIGHT - 1;

	x1 = x1 - World::view_top_x + ZOOM_X1;
	y1 = y1 - World::view_top_y + ZOOM_Y1;
	x2 = x2 - World::view_top_x + ZOOM_X1;
	y2 = y2 - World::view_top_y + ZOOM_Y1;


	if( x1>=ZOOM_X1 && y1>=ZOOM_Y1 && x2<=ZOOM_X2 && y2<=ZOOM_Y2 )
	{
		vga_back.rect( x1, y1, x2, y2, 1, OWN_SELECT_FRAME_COLOR );
	}
}
