GC_clear_stack(void *arg)
{
# ifndef STACK_NOT_SCANNED
    ptr_t sp = GC_approx_sp();
#   ifdef THREADS
        word volatile dummy[SMALL_CLEAR_SIZE];
        static unsigned random_no = 0;


#   endif
    ptr_t limit;

#   define SLOP 400


#   define GC_SLOP 4000


#   define CLEAR_THRESHOLD 100000


#   ifdef THREADS
      if (++random_no % 13 == 0) {
        limit = sp;
        MAKE_HOTTER(limit, BIG_CLEAR_SIZE*sizeof(word));
        limit = (ptr_t)((word)limit & ~0xf);


        return GC_clear_stack_inner(arg, limit);
      } else {
        BZERO((void *)dummy, SMALL_CLEAR_SIZE*sizeof(word));
      }
#   else
      if (GC_gc_no > GC_stack_last_cleared) {

        if (GC_stack_last_cleared == 0)
          GC_high_water = (ptr_t)GC_stackbottom;
        GC_min_sp = GC_high_water;
        GC_stack_last_cleared = GC_gc_no;
        GC_bytes_allocd_at_reset = GC_bytes_allocd;
      }

      MAKE_COOLER(GC_high_water, WORDS_TO_BYTES(DEGRADE_RATE) + GC_SLOP);
      if ((word)sp HOTTER_THAN (word)GC_high_water) {
          GC_high_water = sp;
      }
      MAKE_HOTTER(GC_high_water, GC_SLOP);
      limit = GC_min_sp;
      MAKE_HOTTER(limit, SLOP);
      if ((word)sp COOLER_THAN (word)limit) {
        limit = (ptr_t)((word)limit & ~0xf);


        GC_min_sp = sp;
        return GC_clear_stack_inner(arg, limit);
      } else if (GC_bytes_allocd - GC_bytes_allocd_at_reset
                    > CLEAR_THRESHOLD) {

        GC_min_sp = sp;
        MAKE_HOTTER(GC_min_sp, CLEAR_THRESHOLD/4);
        if ((word)GC_min_sp HOTTER_THAN (word)GC_high_water)
          GC_min_sp = GC_high_water;
        GC_bytes_allocd_at_reset = GC_bytes_allocd;
      }
#   endif
# endif
  return arg;
}
