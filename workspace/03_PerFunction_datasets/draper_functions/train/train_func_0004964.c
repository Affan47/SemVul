rls_stretch_scanline_setup( int XDelta, int YDelta )
{
	  scale_ydelta_minus_1 = YDelta - 1;


      scale_whole_step = XDelta / YDelta;


      scale_adj_up = (XDelta % YDelta) * 2;


      scale_adj_down = YDelta * 2;


      scale_error_term = (XDelta % YDelta) - (YDelta * 2);


      scale_initial_pixel_count = (scale_whole_step / 2) + 1;
      scale_final_pixel_count = scale_initial_pixel_count;


      if ((scale_adj_up == 0) && ((scale_whole_step & 0x01) == 0))
      {
         scale_initial_pixel_count--;
      }


      if ((scale_whole_step & 0x01) != 0)
      {
         scale_error_term += YDelta;
      }

}
