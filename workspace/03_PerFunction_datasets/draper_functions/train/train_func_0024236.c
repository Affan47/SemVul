Hide_line_preview(short start_x,short start_y,short end_x,short end_y)
{
  int w = end_x-start_x, h = end_y - start_y;
  Pixel_figure=Pixel_figure_clear_preview;
  Draw_line_general(start_x,start_y,end_x,end_y,0);
  Update_part_of_screen((start_x<end_x)?start_x:end_x,(start_y<end_y)?start_y:end_y,abs(w)+1,abs(h)+1);
}
