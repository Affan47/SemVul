erase_player (int i)
{
  dmsg (D_MISC, "erase player %d", i);

  if (!in_menu)
    square_occupied[player[i].x2 + player[i].y2 * lvl.square_width] = 0xff;
  if (player[i].way == w_left)
    square_occupied[player[i].y2 * lvl.square_width +
		   ((player[i].x2 - 1) & lvl.square_width_wrap)] = 0xff;
  if (player[i].way == w_right)
    square_occupied[player[i].y2 * lvl.square_width +
		   ((player[i].x2 + 1) & lvl.square_width_wrap)] = 0xff;
  if (player[i].way == w_up)
    square_occupied[player[i].x2 +
		   ((player[i].y2 - 1) & lvl.square_height_wrap)
		   * lvl.square_width] =
      0xff;
  if (player[i].way == w_down)
    square_occupied[player[i].x2 +
		   ((player[i].y2 + 1) & lvl.square_height_wrap)
		   * lvl.square_width] =
      0xff;
}
