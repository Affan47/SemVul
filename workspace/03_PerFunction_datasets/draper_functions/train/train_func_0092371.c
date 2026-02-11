make_angry()
{
 if (is_enemy())
  return;
 if (op_of_u.fear > 10 + personality.aggression + personality.bravery)
  attitude = NPCATT_FLEE;
 else
  attitude = NPCATT_KILL;
}
