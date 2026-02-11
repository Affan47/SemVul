minimal_update(int p, int q) {
  if (q < p) p = q;
  minimal_update(p);
}
