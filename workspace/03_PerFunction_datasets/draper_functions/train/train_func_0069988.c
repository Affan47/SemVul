disp_back_buf(int bltX1, int bltY1, int bltX2, int bltY2)
{
	if( !icon_ptr )
		return;


	if( frame_flag )
		disp_frame(&vga_back);


	if( is_touch(bltX1, bltY1, bltX2, bltY2) )
	{


		int x1 = MAX(cur_x1,bltX1);
		int y1 = MAX(cur_y1,bltY1);
		int x2 = MIN(cur_x2,bltX2);
		int y2 = MIN(cur_y2,bltY2);

		vga_back.read_bitmap( x1, y1, x2, y2, save_back_scr );


		IMGblt( save_scr+4, MIN(cur_x2,VGA_WIDTH-1) -MAX(cur_x1,0)+1, x1-MAX(cur_x1,0), y1-MAX(cur_y1,0), save_back_scr );


		if( cur_x1 < bltX1 || cur_x2 > bltX2 || cur_y1 < bltY1 || cur_y2 > bltY2 )
		{
			vga_back.put_bitmap_area_trans( cur_x1, cur_y1, icon_ptr,
				MAX(bltX1,cur_x1)-cur_x1, MAX(bltY1,cur_y1)-cur_y1,
				MIN(bltX2,cur_x2)-cur_x1, MIN(bltY2,cur_y2)-cur_y1 );
		}


		else
		{
			vga_back.put_bitmap_trans(cur_x1, cur_y1, icon_ptr);
		}

		cursor_shown = 1;
	}
}
