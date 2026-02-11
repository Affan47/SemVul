resolve_ties(struct feature* f)

{
  struct feature* ft;
  struct slurtie* s;
  struct note* m;
  struct note* n;
  int i, j;

  n = f->item;
  for (i=0; i<cv->tiespending; i++) {
    ft = cv->tie_place[i];
    s = ft->item;
    ft = s->begin;
    m = ft->item;
    if (m->y == n->y) {
      s->end = f;
      j = cv->tiespending;
      cv->tie_place[i] = cv->tie_place[j-1];
      cv->tie_status[i] = cv->tie_status[j-1];
      cv->tiespending = j-1;
    };
  };
}
