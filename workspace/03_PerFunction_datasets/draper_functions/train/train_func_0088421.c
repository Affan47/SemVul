update_background(void *data, void *user_data) {
  Graphics_drawinfo *gd = (Graphics_drawinfo *) data;
  Graphics *g = (Graphics *) user_data;
  SDL_Rect rect;

  if (gd->flags && gd->prev.w > 0) {
    rect = gd->prev;
    rect.x -= g->goffset->x;
    rect.y -= g->goffset->y;
    SDL_BlitSurface(g->background,&rect,g->screen,&(gd->prev));
  }
  return TRUE;
}
