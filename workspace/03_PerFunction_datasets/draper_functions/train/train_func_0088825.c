drawgracehead(struct note* n, double x, struct feature* ft,
                          enum tail_type tail)

{
  int i;
  double y;

  y = (double)(TONE_HT*n->y);
  switch (tail) {
  case nostem:

    fprintf(f, "%.1f %.1f gn", x, y);
    break;
  case single:

    fprintf(f, "%.1f %.1f %.1f gn1", x, y, n->stemlength);
    break;
  case midbeam:
  case startbeam:
  case endbeam:

    fprintf(f, "%.1f %.1f %.1f gnt", x, y, n->stemlength);
    break;
  };
  switch (n->accidental) {
  case '=':
    fprintf(f, " %.1f %.1f gnt0", x-ACC_OFFSET, y);
    break;
  case '^':
    if (n->mult == 1) {
      fprintf(f, " %.1f %.1f gsh0", x-ACC_OFFSET, y);
    } else {
      fprintf(f, " %.1f %.1f gds0h", x-ACC_OFFSET, y);
    };
    break;
  case '_':
    if (n->mult == 1) {
      fprintf(f, " %.1f %.1f gft0", x-ACC_OFFSET, y);
    } else {
      fprintf(f, " %.1f %.1f gdf0", x-ACC_OFFSET, y);
    };
    break;
  default:
    break;
  };
  i = 10;
  while (n->y >= i) {
    fprintf(f, " %.1f %.1f ghl", x, (double)i*TONE_HT);
    i = i + 2;
  };
  i = -2;
  while (n->y <= i) {
    fprintf(f, " %.1f %.1f ghl", x, (double)i*TONE_HT);
    i = i - 2;
  };
  fprintf(f, "\n");
}
