invert_and_revcomp_path (struct T *old, int npairs) {
  struct T *new;
  int i, j;

  new = (struct T *) MALLOC(npairs*sizeof(struct T));
  for (i = 0, j = npairs-1; i < npairs; i++, j--) {
    memcpy(&(new[j]),&(old[i]),sizeof(struct T));
    new[j].cdna = complCode[(int) old[i].cdna];
    new[j].genome = complCode[(int) old[i].genome];
    new[j].comp = complCode[(int) old[i].comp];
  }
  return new;
}
