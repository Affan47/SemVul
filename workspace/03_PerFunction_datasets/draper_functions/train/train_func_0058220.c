change_attack(int str, int move, int acode)
{
  str = worm[str].origin;
  DEBUG(DEBUG_WORMS, "change_attack: %1m %1m %d\n", str, move, acode);
  change_tactical_point(str, move, acode,
			worm[str].attack_points, worm[str].attack_codes);
}
