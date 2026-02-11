gnibbles_warpmanager_add_warp (GnibblesWarpManager * warpmanager, gint t_x,
                               gint t_y, gint t_wx, gint t_wy)
{
  gint i, add = 1, draw = 0;

  if (t_x < 0) {
    for (i = 0; i < warpmanager->numwarps; i++) {
      if (warpmanager->warps[i]->wx == t_x) {
        warpmanager->warps[i]->wx = t_wx;
        warpmanager->warps[i]->wy = t_wy;
        return;
      }
    }

    if (warpmanager->numwarps == MAXWARPS)
      return;
    warpmanager->warps[warpmanager->numwarps] =
                gnibbles_warp_new (t_x, t_y, t_wx, t_wy);
    warpmanager->numwarps++;
  } else {
    for (i = 0; i < warpmanager->numwarps; i++) {
      if (warpmanager->warps[i]->x == t_wx) {
        warpmanager->warps[i]->x = t_x;
        warpmanager->warps[i]->y = t_y;
        draw = i;
        add = 0;
      }
    }
    if (add) {
      if (warpmanager->numwarps == MAXWARPS)
        return;
      warpmanager->warps[warpmanager->numwarps] =
                    gnibbles_warp_new (t_x, t_y, t_wx, t_wy);
      draw = warpmanager->numwarps;
      warpmanager->numwarps++;
    }

    board->walls[t_x][t_y] = WARPLETTER;
    board->walls[t_x + 1][t_y] = WARPLETTER;
    board->walls[t_x][t_y + 1] = WARPLETTER;
    board->walls[t_x + 1][t_y + 1] = WARPLETTER;

    gnibbles_warp_draw (warpmanager->warps[draw]);
  }
}
