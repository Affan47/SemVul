renumber_reinf(void) {
  int i, j, pin = 1;
  for ( i = 0; i < SCEN_COUNT; i++ ) {
    for ( j = 0; j < 2; j++ ) {
      Unit *unit;
      list_reset( reinf[j][i] );
      while ((unit = list_next( reinf[j][i] )))
        unit->pin = pin++;
    }
  }
}
