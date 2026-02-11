peel_loop_simple (struct loops *loops, struct loop *loop)
{
  sbitmap wont_exit;
  unsigned npeel = loop->lpt_decision.times;

  wont_exit = sbitmap_alloc (npeel + 1);
  sbitmap_zero (wont_exit);

  if (!duplicate_loop_to_header_edge (loop, loop_preheader_edge (loop),
		loops, npeel, wont_exit, NULL, NULL, NULL,
		DLTHE_FLAG_UPDATE_FREQ))
    abort ();

  free (wont_exit);

  if (rtl_dump_file)
    fprintf (rtl_dump_file, ";; Peeling loop %d times\n", npeel);
}
