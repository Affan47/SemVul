will_be_3_connected(EDGE *e)


{
  int end1, end2;
  EDGE *run, *last;

  end1=e->prev->end;
  end2=e->next->end;

  if (degree[end1]<degree[end2])
    { e=e->prev->invers;
    run=e->next; last=e->prev;


    while (run!=last)
      { if (run->invers->prev->end==end2) return 0;
        run=run->next; }
    }
  else
    { e=e->next->invers;
    run=e->next; last=e->prev;
    while (run!=last)
      { if (run->invers->prev->end==end1) return 0;
        run=run->next; }
    }

  return 1;
}
