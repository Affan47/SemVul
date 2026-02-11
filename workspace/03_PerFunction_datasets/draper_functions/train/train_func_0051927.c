click(int x, int y, int b)
{
  if (get_centered_pic())
  {
    set_centered_pic(0);
    return;
  }

  if (check_layer_buttons(x, y))
    return;
  if (b == 1)
    add_tile(x, y);
  else
    remove_tile(x, y);
}
