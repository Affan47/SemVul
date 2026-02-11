ammo_effects(game *g, int x, int y, long flags)
{
 if (flags & mfb(IF_AMMO_EXPLOSIVE))
  g->explosion(x, y, 24, 0, false);

 if (flags & mfb(IF_AMMO_FRAG))
  g->explosion(x, y, 12, 28, false);

 if (flags & mfb(IF_AMMO_NAPALM))
  g->explosion(x, y, 18, 0, true);

 if (flags & mfb(IF_AMMO_EXPLOSIVE_BIG))
  g->explosion(x, y, 40, 0, false);

 if (flags & mfb(IF_AMMO_TEARGAS)) {
  for (int i = -2; i <= 2; i++) {
   for (int j = -2; j <= 2; j++)
    g->m.add_field(g, x + i, y + j, fd_tear_gas, 3);
  }
 }

 if (flags & mfb(IF_AMMO_SMOKE)) {
  for (int i = -1; i <= 1; i++) {
   for (int j = -1; j <= 1; j++)
    g->m.add_field(g, x + i, y + j, fd_smoke, 3);
  }
 }

 if (flags & mfb(IF_AMMO_FLASHBANG))
  g->flashbang(x, y);

 if (flags & mfb(IF_AMMO_FLAME)) {
  if (g->m.add_field(g, x, y, fd_fire, 1))
   g->m.field_at(x, y).age = 800;
 }

}
