gfx_resize (GtkWidget * w)
{
  int width, height;

  width = gtk_widget_get_allocated_width (w);
  height = gtk_widget_get_allocated_height (w);

  boardsize = MIN (width, height);
  tilesize = boardsize / 7;

  offset[TILE_PLAYER1] = 0;
  offset[TILE_PLAYER2] = tilesize;
  offset[TILE_CLEAR] = tilesize * 2;
  offset[TILE_CLEAR_CURSOR] = tilesize * 3;
  offset[TILE_PLAYER1_CURSOR] = tilesize * 4;
  offset[TILE_PLAYER2_CURSOR] = tilesize * 5;

  gfx_refresh_pixmaps ();
  gfx_draw_all ();
}
