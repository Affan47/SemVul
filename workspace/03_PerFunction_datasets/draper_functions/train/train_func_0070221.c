particle_map(double dxinv, double dyinv,
                               double dzinv, double sft,
                               int ** part2grid, int nup,
                               int nlw, int nxlo_o,
                               int nylo_o, int nzlo_o,
                               int nxhi_o, int nyhi_o,
                               int nzhi_o)
{
  const int * _noalias const type = atom->type;
  const dbl3_t * _noalias const x = (dbl3_t *) atom->x[0];
  int3_t * _noalias const p2g = (int3_t *) part2grid[0];
  const double boxlox = boxlo[0];
  const double boxloy = boxlo[1];
  const double boxloz = boxlo[2];
  const int nlocal = atom->nlocal;

  const double delxinv = dxinv;
  const double delyinv = dyinv;
  const double delzinv = dzinv;
  const double shift = sft;
  const int nupper = nup;
  const int nlower = nlw;
  const int nxlo_out = nxlo_o;
  const int nylo_out = nylo_o;
  const int nzlo_out = nzlo_o;
  const int nxhi_out = nxhi_o;
  const int nyhi_out = nyhi_o;
  const int nzhi_out = nzhi_o;

  int i, flag = 0;
#if defined(_OPENMP)
#pragma omp parallel for private(i) default(none) reduction(+:flag) schedule(static)
#endif
  for (i = 0; i < nlocal; i++) {


    const int nx = static_cast<int> ((x[i].x-boxlox)*delxinv+shift) - OFFSET;
    const int ny = static_cast<int> ((x[i].y-boxloy)*delyinv+shift) - OFFSET;
    const int nz = static_cast<int> ((x[i].z-boxloz)*delzinv+shift) - OFFSET;

    p2g[i].a = nx;
    p2g[i].b = ny;
    p2g[i].t = nz;


    if (nx+nlower < nxlo_out || nx+nupper > nxhi_out ||
        ny+nlower < nylo_out || ny+nupper > nyhi_out ||
        nz+nlower < nzlo_out || nz+nupper > nzhi_out)
      flag++;
  }

  int flag_all;
  MPI_Allreduce(&flag,&flag_all,1,MPI_INT,MPI_SUM,world);
  if (flag_all) error->all(FLERR,"Out of range atoms - cannot compute PPPM");
}
