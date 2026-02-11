find_reinf_by_pin(int pin, int *side_id, int *scen_id) {
  int i, j;
  for ( i = 0; i < SCEN_COUNT; i++ ) {
    for ( j = 0; j < 2; j++ ) {
      Unit *unit;
      list_reset( reinf[j][i] );
      while ((unit = list_next( reinf[j][i] )))
        if (unit->pin == pin) {
          if (scen_id) *scen_id = i;
          if (side_id) *side_id = j;
          return unit;
        }
    }
  }
  return 0;
}
