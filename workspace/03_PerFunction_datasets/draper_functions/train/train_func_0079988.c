pkill_l(game *g, player *p, item *it, bool t)
{
 if (!p->is_npc())
  g->add_msg("You take some %s.", it->tname().c_str());

 p->add_disease(DI_PKILL_L, rng(12, 18) * 300, g);
}
