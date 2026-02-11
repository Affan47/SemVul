tileset_player_free(struct tileset *t, struct player *pplayer)
{
  int plrid, i, j;

  fc_assert_ret(pplayer != NULL);

  plrid = player_index(pplayer);

  if (t->sprites.player[plrid].color) {
    free_sprite(t->sprites.player[plrid].color);
    t->sprites.player[plrid].color = NULL;
  }
  if (t->sprites.player[plrid].background) {
    free_sprite(t->sprites.player[plrid].background);
    t->sprites.player[plrid].background = NULL;
  }

  for (i = 0; i < EDGE_COUNT; i++) {
    for (j = 0; j < 2; j++) {
      if (t->sprites.player[plrid].grid_borders[i][j]) {
        free_sprite(t->sprites.player[plrid].grid_borders[i][j]);
        t->sprites.player[plrid].grid_borders[i][j] = NULL;
      }
    }
  }
}
