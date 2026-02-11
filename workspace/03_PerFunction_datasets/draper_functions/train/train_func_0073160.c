calc_median_gap(struct tlines * lines) {
  int gaps[MAXlines], l;
  if (lines->num<2) return 0;
  for (l = 0; l < lines->num - 1; l++)
    gaps[l] = lines->m2[l + 1] - lines->m3[l];
  qsort(gaps, lines->num - 1, sizeof(gaps[0]), intcompare);
  return gaps[(lines->num - 1) / 2];
}
