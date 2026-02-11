egbb_stats(void) {

   if (Egbb->init == 1) {
      return Egbb->read_hit;
   } else {
      return 0;
   }
}
