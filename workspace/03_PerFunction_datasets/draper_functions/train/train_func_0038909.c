Vertical_XOR_line_double(word x_pos,word y_pos,word height)
{
  int i;
  byte *dest=Screen_pixels+x_pos*ZOOMX+y_pos*VIDEO_LINE_WIDTH*ZOOMY;
  for (i=height;i>0;i--)
  {
    *dest=*(dest+1)=*(dest+VIDEO_LINE_WIDTH)=*(dest+VIDEO_LINE_WIDTH+1)=~*dest;
    dest+=VIDEO_LINE_WIDTH*ZOOMY;
  }
}
