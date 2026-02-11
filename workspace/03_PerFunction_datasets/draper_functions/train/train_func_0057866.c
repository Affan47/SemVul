grenade_act(game *g, player *p, item *it, bool t)
{
 point pos = g->find_item(it);
 if (pos.x == -999 || pos.y == -999)
  return;
 if (t)
  g->sound(pos.x, pos.y, 0, "Tick.");
 else
  g->explosion(pos.x, pos.y, 12, 28, false);
}
