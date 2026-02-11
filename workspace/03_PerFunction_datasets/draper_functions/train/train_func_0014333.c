Invert_vector (int event_x, int event_y)


{
  struct data *hdc;
  int tmp_x, tmp_y;

  hdc = select_vector (event_x, event_y, size_factor);
  if (!hdc)
    return;
  tmp_x = hdc->x;
  tmp_y = hdc->y;
  hdc->x = hdc->tx;
  hdc->y = hdc->ty;
  hdc->tx = tmp_x;
  hdc->ty = tmp_y;
  modify = True;
  Display_Mol ();
}
