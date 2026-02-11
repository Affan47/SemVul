get_backtrellis_words(RecogProcess *r, NEXTWORD **nw, NODE *hypo, short tm, short t_end)
{
  int num = 0;
  int t, t_step;
  int oldnum=0;

  BACKTRELLIS *bt;
  int lookup_range;

  if (tm < 0) return(0);

  bt = r->backtrellis;
  lookup_range = r->config->pass2.lookup_range;

#ifdef PREFER_CENTER_ON_TRELLIS_LOOKUP


  for (t_step = 0; t_step < lookup_range; t_step++) {

    t = tm - t_step;
    if (t < 0 || t > bt->framelen - 1 || t >= t_end) continue;
    num = pick_backtrellis_words(r, nw, oldnum, hypo, t);
    if (num > oldnum) {
      qsort(nw, num, sizeof(NEXTWORD *),
	    (int (*)(const void *,const void *))compare_nw);
      oldnum = num;
    }
    if (t_step == 0) continue;

    t = tm + t_step;
    if (t < 0 || t > bt->framelen - 1 || t >= t_end) continue;
    num = pick_backtrellis_words(r, nw, oldnum, hypo, t);
    if (num > oldnum) {
      qsort(nw, num, sizeof(NEXTWORD *),
	    (int (*)(const void *,const void *))compare_nw);
      oldnum = num;
    }
  }

#else


  for(t = tm; t >= tm - lookup_range; t--) {
    if (t < 0) break;
    num = pick_backtrellis_words(r, nw, oldnum, hypo, t);
    if (num > oldnum) {
      qsort(nw, num, sizeof(NEXTWORD *),
	    (int (*)(const void *,const void *))compare_nw);
      oldnum = num;
    }
  }

  for(t = tm + 1; t < tm + lookup_range; t++) {
    if (t > bt->framelen - 1) break;
    if (t >= t_end) break;
    num = pick_backtrellis_words(r, nw, oldnum, hypo, t);
    if (num > oldnum) {
      qsort(nw, num, sizeof(NEXTWORD *),
	    (int (*)(const void *,const void *))compare_nw);
      oldnum = num;
    }
  }
#endif

  return num;
}
