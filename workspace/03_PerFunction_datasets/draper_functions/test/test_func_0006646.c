he_clear_get(command_mode)
  int command_mode;


{
  int key1, key2 = 0;

  tio_ungetch(tio_tget(1));
  while ((key1 = tio_get())) {
    key2 = key1;
    switch (key1) {
    HE_CASE_MOTION:
      break;
    HE_CASE_MOTION_SHIFT:
    HE_CASE_MOTION_HJKL:
      if (command_mode) break;
    default:
      key1 = 0;
    }
    if (key1) continue;
    break;
  }
  if (key2) {
    tio_ungetch(key2);
    return 1;
  }
  return 0;
}
