monospace(struct tune* t)
{
  int doneline;
  struct voice* v;

  v = firstitem(&t->voices);
  while (v != NULL) {
    doneline = 1;
    v->place = v->first;
    while (doneline == 1) {
      doneline = spaceline(v);
    };
    v = nextitem(&t->voices);
  };
}
