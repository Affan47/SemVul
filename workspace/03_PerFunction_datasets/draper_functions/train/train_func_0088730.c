action_one_greedy (struct king *k, struct grid *g, struct flag_grid *fg) {
  int i, j;
  int i_best = 0, j_best = 0;
  float v_best = -1.0;
  for (i=0; i<g->width; ++i) {
    for (j=0; j<g->height; ++j) {
      if (fg->flag[i][j])
        remove_flag(g, fg, i, j, FLAG_POWER);


      int army = g->tiles[i][j].units[k->pl][citizen];
      int enemy = 0;
      int p;
      for (p=0; p<MAX_PLAYER; ++p) {
        if (p!= k->pl)
          enemy = enemy + g->tiles[i][j].units[p][citizen];
      }
      float v = (float) k->value[i][j] * (5.0*enemy - army) * pow(army, 0.5);

      if (v > v_best && v > 5000) {v_best = v; i_best = i; j_best = j;}
    }
  }
  if (v_best > 0)
    add_flag(g, fg, i_best, j_best, FLAG_POWER);
}
