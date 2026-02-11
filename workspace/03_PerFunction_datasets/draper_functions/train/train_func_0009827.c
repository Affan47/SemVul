pick_and_eat(game *g)
{
 int best_hunger = 999, best_thirst = 999, index = -1;
 bool thirst_more_important = (thirst > hunger * 1.5);
 for (int i = 0; i < inv.size(); i++) {
  int eaten_hunger = -1, eaten_thirst = -1;
  it_comest* food = NULL;
  if (inv[i].is_food())
   food = dynamic_cast<it_comest*>(inv[i].type);
  else if (inv[i].is_food_container())
   food = dynamic_cast<it_comest*>(inv[i].contents[0].type);
  if (food != NULL) {
   eaten_hunger = hunger - food->nutr;
   eaten_thirst = thirst - food->quench;
  }
  if (eaten_hunger > 0) {
   if ((thirst_more_important && eaten_thirst < best_thirst) ||
       (!thirst_more_important && eaten_hunger < best_hunger) ||
       (eaten_thirst == best_thirst && eaten_hunger < best_hunger) ||
       (eaten_hunger == best_hunger && eaten_thirst < best_thirst)   ) {
    if (eaten_hunger < best_hunger)
     best_hunger = eaten_hunger;
    if (eaten_thirst < best_thirst)
     best_thirst = eaten_thirst;
    index = i;
   }
  }
 }

 if (index == -1) {
  debugmsg("NPC tried to eat food, but couldn't find any!");
  move_pause();
  return;
 }

 eat(g, index);
 moves = 0;
}
