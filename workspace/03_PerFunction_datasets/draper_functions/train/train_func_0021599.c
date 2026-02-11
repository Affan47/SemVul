rx_dupe(struct stuff *s)
{
  int result = 0;
  static char *lupedupe[] = {"dupe or loop","dupe","loop"};


  if (Kill_dupes && dupe_packet(&s->in,s->cp,s->len)) {
    ++s->i->stats.rx_dup;
    result = 1;
  } else if (Kill_loops && loop_packet(&s->in,s->cp,s->len)) {
    ++s->i->stats.rx_loop;
    result = 2;
  }
  if (Verbose) {
    fprintf(stderr,"packet is%sa %s\n",result?" ":" not ",lupedupe[result]);
  }
  return result;
}
