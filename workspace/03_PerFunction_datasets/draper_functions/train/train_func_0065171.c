rand_terrain_by_flag(enum terrain_flag_id flag)
{
  int num = 0;
  struct terrain *terr = NULL;

  terrain_type_iterate(pterr) {
    if (terrain_has_flag(pterr, flag)) {
      num++;
      if (fc_rand(num) == 1) {
        terr = pterr;
      }
    }
  } terrain_type_iterate_end;

  return terr;
}
