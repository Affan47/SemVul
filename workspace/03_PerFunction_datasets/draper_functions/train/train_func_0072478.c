is_4bangle_centre(EDGE *e)


{
  EDGE *run, *run1, *last, *last1, *dummy;


  RESETMARKS_V;

  dummy=e->next->invers;
  last=dummy->prev;
  run=dummy->next->next;
  MARK_V(run->end);
  while (run!=last)
    { run=run->next;
      MARK_V(run->end);
    }

  e=e->prev->invers;

  run=e->next;
  last=e->prev->prev;
    dummy=run->invers;
    last1=dummy->prev->prev;
    run1=dummy->next->next;
    if (ISMARKED_V(run1->end)) return 1;
    run1=run1->next;
    if (ISMARKED_V(run1->end)) return 1;
    while (run1!=last1)
      { run1=run1->next; if (ISMARKED_V(run1->end)) return 1; }
  while (run!=last)
    { run=run->next;
      dummy=run->invers;
      last1=dummy->prev->prev;
      run1=dummy->next->next;
      if (ISMARKED_V(run1->end)) return 1;
      run1=run1->next;
      if (ISMARKED_V(run1->end)) return 1;
      while (run1!=last1)
        { run1=run1->next; if (ISMARKED_V(run1->end)) return 1; }
    }

  return 0;
}
