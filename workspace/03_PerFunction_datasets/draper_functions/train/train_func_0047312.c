sweep_phase(void) {

  STATIC long j, k;
  STATIC object x;
  STATIC char *p;
  STATIC struct typemanager *tm;
  STATIC object f;
  STATIC struct pageinfo *v;

  for (v=cell_list_head;v;v=v->next) {

    tm = tm_of((enum type)v->type);

    p = pagetochar(page(v));
    f = tm->tm_free;
    k = 0;
    for (j = tm->tm_nppage; j > 0; --j, p += tm->tm_size) {
      x = (object)p;
      if (is_free(x))
	continue;
      else if (is_marked(x)) {
	unmark(x);
	continue;
      }

      SET_LINK(x,f);
      make_free(x);
      f = x;
      k++;
    }
    tm->tm_free = f;
    tm->tm_nfree += k;
    pagetoinfo(page(v))->in_use-=k;

  }

}
