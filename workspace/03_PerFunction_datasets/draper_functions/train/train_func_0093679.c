TimeLeft(void) {
  static Uint32 next_time = 0;
  Uint32 now,res;
  static Uint32 tick = 0;
  static int i = 0;
  now = SDL_GetTicks();
  if (i == 0) {
    if (tick != 0)
      INFO(_("FPS: %d"),(30 * 1000)/(now-tick));
    tick = now;
    i = 30;
  }
  i--;
  if (next_time <= now) {
    next_time = now + TICK_INTERVAL;
    return 0;
  }
  res = next_time - now;
  next_time += TICK_INTERVAL;
  return res;
}
