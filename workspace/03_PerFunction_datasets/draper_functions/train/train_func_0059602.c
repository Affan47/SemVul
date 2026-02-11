crossbow(game *g, monster *z, int x, int y)
{
 int t;
 bool add_bolt = true;
 bool seen = g->u_see(z, t);
 if (!one_in(4)) {
  if (seen)
   g->add_msg("A bolt shoots out and hits the %s!", z->name().c_str());
  if (z->hurt(rng(20, 30)))
   g->kill_mon(g->mon_at(x, y));
  add_bolt = !one_in(10);
 } else if (seen)
  g->add_msg("A bolt shoots out, but misses the %s.", z->name().c_str());
 g->m.tr_at(x, y) = tr_null;
 g->m.add_item(x, y, g->itypes[itm_crossbow], 0);
 g->m.add_item(x, y, g->itypes[itm_string_6], 0);
 if (add_bolt)
  g->m.add_item(x, y, g->itypes[itm_bolt_steel], 0);
}
