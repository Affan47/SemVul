wield_best_melee(game *g)
{
 int best_score = 0, index = -1;
 for (int i = 0; i < inv.size(); i++) {
  int score = inv[i].melee_value(sklevel);
  if (score > best_score) {
   best_score = score;
   index = i;
  }
 }
 if (index == -1) {
  debugmsg("npc::wield_best_melee failed to find a melee weapon.");
  move_pause();
  return;
 }
 wield(g, index);
}
