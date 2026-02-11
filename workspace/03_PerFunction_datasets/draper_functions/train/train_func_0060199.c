give_equipment(game *g, npc *p)
{
 std::vector<int> giving;
 std::vector<int> prices;
 p->init_selling(giving, prices);
 int chosen = -1;
 if (giving.empty()) {
  for (int i = 0; i < p->inv.size(); i++) {
   int val = p->value(p->inv[i]) - p->inv[i].price() / 50;
   giving.push_back(i);
   prices.push_back(p->inv[i].price());
  }
 }
 while (chosen == -1 && giving.size() > 1) {
  int index = rng(0, giving.size() - 1);
  if (prices[index] < p->op_of_u.owed)
   chosen = index;
  giving.erase(giving.begin() + index);
  prices.erase(prices.begin() + index);
 }
 if (giving.empty()) {
  popup("%s has nothing to give!", p->name.c_str());
  return;
 }
 if (chosen == -1)
  chosen = 0;
 int item_index = giving[chosen];
 popup("%s gives you a %s.", p->name.c_str(),
       p->inv[item_index].tname().c_str());
 g->u.i_add( p->i_remn(item_index) );
 p->op_of_u.owed -= prices[chosen];
}
