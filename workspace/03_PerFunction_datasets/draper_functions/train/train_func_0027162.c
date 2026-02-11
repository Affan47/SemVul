gnibbles_worm_reverse (gpointer data)
{
  GnibblesWorm *worm = (GnibblesWorm *) data;
  gint tmp, old_dir;

  old_dir = gnibbles_worm_get_tail_direction (worm);

  worm->list = g_list_reverse (worm->list);

  tmp = worm->xhead;
  worm->xhead = worm->xtail;
  worm->xtail = tmp;
  tmp = worm->yhead;
  worm->yhead = worm->ytail;
  worm->ytail = tmp;
  tmp = worm->yhead;

  if (old_dir == WORMRIGHT)
    worm->direction = WORMLEFT;
  else if (old_dir == WORMLEFT)
    worm->direction = WORMRIGHT;
  else if (old_dir == WORMUP)
    worm->direction = WORMDOWN;
  else if (old_dir == WORMDOWN)
    worm->direction = WORMUP;

  return FALSE;
}
