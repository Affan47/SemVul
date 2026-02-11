initlookup_cossin_table(void) {
  long i;

  for (i = 0; i < MAX_CIRCLE_ANGLE ; i++) {
     fast_cossin_table[i] = (float)sin((double)i * M_PI / HALF_MAX_CIRCLE_ANGLE);
  }
}
