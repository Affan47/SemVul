stencil_half_multi_2d_newton(NeighList *list,
                                            int sx, int sy, int sz)
{
  int i,j,n;
  double rsq,typesq;
  int *s;
  double *distsq;

  int *nstencil_multi = list->nstencil_multi;
  int **stencil_multi = list->stencil_multi;
  double **distsq_multi = list->distsq_multi;

  int ntypes = atom->ntypes;
  for (int itype = 1; itype <= ntypes; itype++) {
    typesq = cuttypesq[itype];
    s = stencil_multi[itype];
    distsq = distsq_multi[itype];
    n = 0;
    for (j = 0; j <= sy; j++)
      for (i = -sx; i <= sx; i++)
        if (j > 0 || (j == 0 && i > 0)) {
          rsq = bin_distance(i,j,0);
          if (rsq < typesq) {
            distsq[n] = rsq;
            s[n++] = j*mbinx + i;
          }
        }
    nstencil_multi[itype] = n;
  }
}
