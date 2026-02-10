adj_gtab_win_pos()
{
  if (!gwin_gtab)
    return;
  if (win_size_exceed(gwin_gtab))
    move_win_gtab(current_in_win_x, current_in_win_y);
}
