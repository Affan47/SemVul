getVScreenOf (int x, int y)
{
  virtualScreen *vs;
  for (vs = Scr->vScreenList; vs != NULL; vs = vs->next) {
    if ((x >= vs->x) && ((x - vs->x) < vs->w) &&
	(y >= vs->y) && ((y - vs->y) < vs->h)) {
        return vs;
    }
  }
  return Scr->vScreenList;
}
