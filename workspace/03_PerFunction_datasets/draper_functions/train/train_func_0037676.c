dirty_rect_bg(SDL_Rect *r)
{
  int then = 1 - drawto;
  if ((!all_dirty[then]) && (r->w > 0) && (r->h > 0)
      && (r->x < width)
      && (r->y < height))
    {
      int xs,xe,ys,ye,i,j;
      xs = r->x / DIRTY_TILE_SIZE;
      ys = r->y / DIRTY_TILE_SIZE;
      xe = (r->x + r->w - 1) / DIRTY_TILE_SIZE;
      ye = (r->y + r->h - 1) / DIRTY_TILE_SIZE;
      for (i=ys;i<=ye;i++)
	for (j = xs; j <= xe; j++)
	  dirty_mask[then][i] |= (unsigned long)1 << j;
    }
}
