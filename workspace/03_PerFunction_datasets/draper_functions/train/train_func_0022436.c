upper_covers(Interp p, int lattice_number)
{
  int n = interp_size(p);
  BOOL *lt = malloc(n * n * sizeof(BOOL *));
  BOOL *uc = malloc(n * n * sizeof(BOOL *));
  int i, j;
  int *a;
  a = interp_table(p, "^", 2);
  if (a == NULL) {
    a = interp_table(p, "meet", 2);
    if (a == NULL) {
      a = interp_table(p, "m", 2);
      if (a == NULL)
	fatal_error("upper_covers: meet not found");
    }
  }


  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      lt[I2(n,i,j)] = (a[I2(n,i,j)] == i && i != j);
      uc[I2(n,i,j)] = lt[I2(n,i,j)];
    }


  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (lt[I2(n,i,j)] && !adjacent(n, i, j, lt))
	uc[I2(n,i,j)] = FALSE;
    }


  printf("%% UPPER-COVERS of Lattice %d\n", lattice_number);
  printf("(\n");
  for (i = 0; i < n; i++) {
    BOOL started = FALSE;
    printf("(%d (", i);
    for (j = 0; j < n; j++) {
      if (uc[I2(n,i,j)]) {
	printf("%s%d", started ? " " : "", j);
	started = TRUE;
      }
    }
    printf("))\n");
  }
  printf(")\n");
  printf("%% end of upper-covers\n");

  free(lt);
  free(uc);
}
