initial_integrate(int vflag) {


  double **x = atom->x;
  double **v = atom->v;
  double **f = atom->f;
  double **vest = atom->vest;
  double *rho = atom->rho;
  double *drho = atom->drho;
  double *e = atom->e;
  double *de = atom->de;
  double *mass = atom->mass;
  double *rmass = atom->rmass;
  int rmass_flag = atom->rmass_flag;

  int *type = atom->type;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;
  int i;
  double dtfm;

  if (igroup == atom->firstgroup)
    nlocal = atom->nfirst;

  for (i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) {
      if (rmass_flag) {
        dtfm = dtf / rmass[i];
      } else {
        dtfm = dtf / mass[type[i]];
      }

      e[i] += dtf * de[i];
      rho[i] += dtf * drho[i];


      vest[i][0] = v[i][0] + 2.0 * dtfm * f[i][0];
      vest[i][1] = v[i][1] + 2.0 * dtfm * f[i][1];
      vest[i][2] = v[i][2] + 2.0 * dtfm * f[i][2];

      v[i][0] += dtfm * f[i][0];
      v[i][1] += dtfm * f[i][1];
      v[i][2] += dtfm * f[i][2];

      x[i][0] += dtv * v[i][0];
      x[i][1] += dtv * v[i][1];
      x[i][2] += dtv * v[i][2];
    }
  }
}
