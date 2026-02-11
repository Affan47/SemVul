biphase(double acc) {
  static double prev_acc = 0;
  static int    counter = 0;
#ifndef DEBUG
  static int    reading_frame  = 0;
  static int    tot_errs[2]     = {0};
#endif

  if (sign(acc) != sign(prev_acc)) {
    tot_errs[counter % 2] ++;
  }

  if (counter % 2 == reading_frame) {
    print_delta(sign(acc + prev_acc));
  }
  if (counter == 0) {
    if (tot_errs[1 - reading_frame] < tot_errs[reading_frame]) {
      reading_frame = 1 - reading_frame;
    }
#ifdef DEBUG
    qua = (1.0 * abs(tot_errs[0] - tot_errs[1]) /
          (tot_errs[0] + tot_errs[1])) * 100;
    fprintf(stderr, "frame: %d  errs: %3d %3d  qual: %3.0f%%  pll: %.1f (%.1f ppm)\n",
        reading_frame, tot_errs[0], tot_errs[1], qua, fsc, (57000.0-fsc)/57000.0*1000000  );
#endif
    tot_errs[0] = 0;
    tot_errs[1] = 0;
  }

  prev_acc = acc;
  counter = (counter + 1) % 800;
}
