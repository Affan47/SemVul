stumble(game *g, bool moved)
{
 std::vector <point> valid_stumbles;
 for (int i = -1; i <= 1; i++) {
  for (int j = -1; j <= 1; j++) {
   if (can_move_to(g->m, posx + i, posy + j) &&
       (g->u.posx != posx + i || g->u.posy != posy + j) &&
       (g->mon_at(posx + i, posy + j) == -1 || (i == 0 && j == 0))) {
    point tmp(posx + i, posy + j);
    valid_stumbles.push_back(tmp);
   }
  }
 }
 if (valid_stumbles.size() > 0 && (one_in(8) || (!moved && one_in(3)))) {
  int choice = rng(0, valid_stumbles.size() - 1);
  posx = valid_stumbles[choice].x;
  posy = valid_stumbles[choice].y;
  if (!has_flag(MF_DIGS) || !has_flag(MF_FLIES))
   moves -= (g->m.move_cost(posx, posy) - 2) * 50;


  if (plans.size() > 0) {
   int tc;
   if (g->m.sees(posx, posy, plans[0].x, plans[0].y, -1, tc)) {

    std::vector <point> plans2;
    for (int i = 0; i < plans.size(); i++)
     plans2.push_back(plans[i]);

    set_dest(plans[0].x, plans[0].y, tc);

    for (int index = 0; index < plans2.size(); index++)
     plans.push_back(plans2[index]);
   } else
    plans.clear();
  }
 }
}
