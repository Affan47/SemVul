compute_dragon_weakness_value(int d)
{
  int origin = dragon2[d].origin;
  float weakness;


  DEBUG(DEBUG_DRAGONS, "Computing weakness of dragon at %1m:\n", origin);

  weakness = crude_dragon_weakness(dragon2[d].safety, &dragon2[d].genus,
				   dragon2[d].lunch != NO_MOVE,
      				   dragon2[d].moyo_territorial_value,
				   (float) dragon2[d].escape_route);


  if (!dragon2[d].owl_attack_certain)
    weakness += gg_min(0.25 * (1.0 - weakness), 0.25 * weakness);
  if (!dragon2[d].owl_defense_certain)
    weakness += gg_min(0.25 * (1.0 - weakness), 0.25 * weakness);
  if (dragon2[d].owl_threat_status == CAN_THREATEN_ATTACK)
    weakness += 0.15 * (1.0 - weakness);

  if (weakness < 0.0)
    weakness = 0.0;
  if (weakness > 1.0)
    weakness = 1.0;

  DEBUG(DEBUG_DRAGONS, " result: %f.\n", weakness);
  return weakness;
}
