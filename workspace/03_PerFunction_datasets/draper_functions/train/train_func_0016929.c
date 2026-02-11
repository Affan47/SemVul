gnibbles_worm_is_move_safe (GnibblesWorm * worm)
{
  int x, y, i;

  gnibbles_worm_position_move_head(worm, &x, &y);

  for (i = 0; i < properties->numworms; i++) {
    if (i != worm->number) {
      if (gnibbles_worm_can_move_to (worms[i], x, y))
        return (FALSE);
    }
  }

  return TRUE;
}
