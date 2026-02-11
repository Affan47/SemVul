screen_count() {
  if (num_screens < 0) screen_init();

  return num_screens ? num_screens : 1;
}
