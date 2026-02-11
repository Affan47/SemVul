draw_dot()
{
	char*	  vgaBufPtr = vga_back.buf_ptr();
	char*	  writePtr;
	int	  i, mapX, mapY;
	Site*	  rawPtr;


	int		vgaBufPitch = vga_back.buf_pitch();


	for(i=1; i <=size() ; i++)
	{
		if( is_deleted(i) )
			continue;

		rawPtr = operator[](i);

		mapX = MAP_X1 + rawPtr->map_x_loc;
		mapY = MAP_Y1 + rawPtr->map_y_loc;

		if( mapX == MAP_WIDTH-1 )
			mapX = MAP_WIDTH-2;

		if( mapY == MAP_HEIGHT-1 )
			mapY = MAP_HEIGHT-2;


		writePtr = vgaBufPtr + mapY*vgaBufPitch + mapX;

		if( writePtr[-vgaBufPitch-1] != UNEXPLORED_COLOR )
			writePtr[-vgaBufPitch-1] = (char) SITE_COLOR;

		if( writePtr[-vgaBufPitch] != UNEXPLORED_COLOR )
			writePtr[-vgaBufPitch] = (char) SITE_COLOR;

		if( writePtr[-vgaBufPitch+1] != UNEXPLORED_COLOR )
			writePtr[-vgaBufPitch+1] = (char) SITE_COLOR;

		if( writePtr[-1] != UNEXPLORED_COLOR )
			writePtr[-1] = (char) SITE_COLOR;

		if( writePtr[0] != UNEXPLORED_COLOR )
			writePtr[0] = (char) SITE_COLOR;

		if( writePtr[1] != UNEXPLORED_COLOR )
			writePtr[1] = (char) SITE_COLOR;

		if( writePtr[vgaBufPitch-1] != UNEXPLORED_COLOR )
			writePtr[vgaBufPitch-1] = (char) SITE_COLOR;

		if( writePtr[vgaBufPitch] != UNEXPLORED_COLOR )
			writePtr[vgaBufPitch] = (char) SITE_COLOR;

		if( writePtr[vgaBufPitch+1] != UNEXPLORED_COLOR )
			writePtr[vgaBufPitch+1] = (char) SITE_COLOR;


	}
}
