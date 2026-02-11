Pixel_figure_preview(word x_pos,word y_pos,byte color)
  {
    if ( (x_pos>=Limit_left) &&
         (x_pos<=Limit_right) &&
         (y_pos>=Limit_top)   &&
         (y_pos<=Limit_bottom) )
      Pixel_preview(x_pos,y_pos,color);
  }
