lprint ( FILE * f, LISTID lid )
{
  LIST * l;
  LISTNODE * ln;
  NODEPOOL * np;
  int count;

  l = (LIST *)lid;

  fprintf ( f, "list id %p internal data structures:\n",
            lid );
#if CHECK_MAGIC
  if ((l->magic1 != MAGIC) || (l->magic2 != MAGIC)) {
    fprintf ( f, "  *** WARNING: LIST MAGIC IS CORRUPT ***\n" );
  }
  fprintf ( f,
            "  magic1=0x%08x\n"
            "  magic2=0x%08x\n",
            l->magic1, l->magic2 );
#endif
  fprintf ( f, "   num f pool n_ln        top     bottom    next_ln     np_top  np_bottom\n" );
  fprintf ( f, "  ---- - ---- ---- ---------- ---------- ---------- ---------- ----------\n" );
  fprintf ( f, "  %4d %1d %4d %4d %10p %10p %10p %10p %10p\n",
            l->num, l->free_on_close, l->poolsize, l->n_ln_pool,
            l->top, l->bottom,
            l->next_ln, l->np_top, l->np_bottom );


  fprintf ( f,
            "  node pools:\n"
            "     idx         np     magic1       next       prev     magic2\n"
            "    ---- ---------- ---------- ---------- ---------- ----------\n" );
  count = 0;
  np = l->np_top;
  while (np != NULL) {
    count++;
    fprintf ( f, "    %4d %10p 0x%08x %10p %10p 0x%08x\n",
              count, np,
#if CHECK_MAGIC
              np->magic1,
#else
              0,
#endif
              np->chain_next, np->chain_prev,
#if CHECK_MAGIC
              np->magic2
#else
              0
#endif
      );
    np = np->chain_next;
  }

  if (f) {
    fprintf ( f,
              "  list elements:\n"
              "       n         ln     magic1       next       prev       data     magic2\n"
              "    ---- ---------- ---------- ---------- ---------- ---------- ----------\n" );
    count = 0;
    ln = l->top;
    while (ln != NULL) {
      count++;
      fprintf ( f, "    %4d %10p %10x %10p %10p %10p %10x\n",
                count, ln,
#if CHECK_MAGIC
                ln->magic1,
#else
                0,
#endif
                ln->next, ln->prev, ln->data,
#if CHECK_MAGIC
                ln->magic2
#else
                0
#endif
        );
      ln = lnext(ln);
    }
    if (count != l->num) {
      fprintf ( f,
                "  *** list count is not correct\n"
                "  *** list id indicates %d, counted items = %d\n",
                l->num, count );
    }
  }

  return 0;
}
