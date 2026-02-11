rem_effect(monster_effect_type effect)
{
 for (int i = 0; i < effects.size(); i++) {
  if (effects[i].type == effect) {
   effects.erase(effects.begin() + i);
   i--;
  }
 }
}
