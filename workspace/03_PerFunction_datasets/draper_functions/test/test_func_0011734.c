search_rgb(Fl_Widget *, long)
{
  int r, g, b, i;
  int top  = colbr->topline();

  r = int(rs->value());
  g = int(gs->value());
  b = int(bs->value());


  Fl::set_color(FL_FREE_COL4, r, g, b);
  rescol->redraw();
  i = search_entry(r, g, b);

  if(i < top || i > (top+15))
    colbr->topline(i-8);
  colbr->select(i+1, 1);

}
