sdl_get_chance_to_win(int *att_chance, int *def_chance,
		       		struct unit *enemy_unit, struct unit *my_unit)
{

  if (!my_unit || !enemy_unit) {
    return FALSE;
  }


  *att_chance = unit_win_chance(my_unit, enemy_unit) * 100;


  *def_chance = (1.0 - unit_win_chance(enemy_unit, my_unit)) * 100;

  return TRUE;
}
