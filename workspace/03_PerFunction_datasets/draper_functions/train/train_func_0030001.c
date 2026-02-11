draw_radar_map (a_square_coord dx, a_square_coord dy, int radar_shift)
{
  a_pixel *src = corner[0] + 5 * xbuf + 239 + radar_shift;
  unsigned int x, y, tdym;
  a_square_coord tdx, tdy;
  signed char tmp;
  long blink = read_htimer (blink_htimer) & 2;


  if (radar_shift >= 81)
    return;

  draw_radar_frame (src);
  src += xbuf + 1;


  tdy = dy - 20;
  for (y = 40; y; --y) {
    tdy &= lvl.square_height_wrap;
    if (tdy < lvl.square_height) {
      tdym = tdy * lvl.square_width;
      tdx = dx - 36;
      for (x = 73; x; --x) {
	tdx &= lvl.square_width_wrap;
	if (tdx < lvl.square_width) {
	  tmp = tile_bonus[square_tile[tdx + tdym]];

	  if (tmp != 0 && tmp != -1) {

	    if ((tmp & 127) == 1 && blink)
	      *src = 31;
	    else
	      *src = 27;
	  } else {

	    if ((tmp = square_occupied[tdx + tdym]) != -1)
	      *src = radar_trail_color[tmp];

	    else if ((tmp = lvl.square_walls_out[tdx + tdym]) != 0)
	      *src = radar_wall_color[tmp];

	    else
	      *src = glenz[0][*src];
	  }
	} else {


	  *src = glenz[0][*src];
	}
	src++;
	tdx++;
      }
    } else {


      for (x = 73; x; --x, ++src)
	*src = glenz[0][*src];
    }
    src += xbuf - 73;
    tdy++;
  }
}
