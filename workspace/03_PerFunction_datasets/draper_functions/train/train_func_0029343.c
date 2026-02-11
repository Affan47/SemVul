click(int x, int y, int b)
{
  Picture *p = get_centered_pic();
  set_centered_pic(0);
  if (p == splash)
    return;
  if (p == youwin || p == youlose || solution_shown)
  {
    start_again();
    invalidate(0, 0, table_width, table_height);
    return;
  }
  drag_ox = x;
  drag_oy = y;
  if (x >= px && x < px+BSZ && y >= py && y < py+6*pdy)
  {
    color_dragged = colors[(y-py)/pdy];
    drag_dx = x - px;
    drag_dy = y - (((int)((y-py)/pdy))*pdy+py);
    return;
  }
  if (x >= gx && x < gx+4*gdx && y < gy+BSZ && y > gy+(MOVES-1)*gdy)
  {
    int ty;
    ty = ((gy+BSZ)-y)/(-gdy);
    color_dragged = guesses[ty][(x-gx)/gdx];
    if (color_dragged == bighole)
      color_dragged = 0;
    drag_dx = x - (((int)((x-gx)/gdx))*gdx+gx);
    ty = gy+ty*gdy;
    drag_dy = y - ty;
    return;
  }
  color_dragged = 0;
  if (x > rx-WGAP/2)
    check_row();
}
