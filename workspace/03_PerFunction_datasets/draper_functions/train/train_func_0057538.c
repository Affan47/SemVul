dig(game *g, player *p, item *it, bool t)
{
 int dirx, diry;
 g->draw();
 mvprintw(0, 0, "Prospect for clay where??");
 get_direction(dirx, diry, input());
 if (dirx == -2) {
  g->add_msg("Invalid direction.");
  return;
 }
 dirx += p->posx;
 diry += p->posy;
 ter_id type = g->m.ter(dirx, diry);
  if (g->m.ter(dirx, diry) == t_claydirt) {
  if (!one_in(6)) {
    g->add_msg("You find no clay");
    p->moves -= 200;
    g->m.ter(dirx, diry) = t_dirtmound;
 } else {
    p->moves -= 200;
    g->m.ter(dirx, diry) = t_dirtmound;
    g->add_msg("You find some clay!");
     int clays = rng(2, 10);
     item clay(g->itypes[itm_clay], 0, g->nextinv);
      for (int i = 0; i < clays; i++)
      g->m.add_item(dirx, diry, clay);
   }
  }


}
