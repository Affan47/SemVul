final_integrate()
{
  double * const * const v = atom->v;
  const double * const * const f = atom->f;
  double * const * const omega = atom->omega;
  const double * const * const torque = atom->torque;
  const double * const rmass = atom->rmass;
  const double * const radius = atom->radius;
  const int * const mask = atom->mask;
  const int nlocal = (igroup == atom->firstgroup) ? atom->nfirst : atom->nlocal;
  int i;


  const double dtfrotate = dtf / INERTIA;


#if defined(_OPENMP)
#pragma omp parallel for private(i) default(none)
#endif
  for (i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) {
      const double dtfm = dtf / rmass[i];
      v[i][0] += dtfm * f[i][0];
      v[i][1] += dtfm * f[i][1];
      v[i][2] += dtfm * f[i][2];

      const double dtirotate = dtfrotate / (radius[i]*radius[i]*rmass[i]);
      omega[i][0] += dtirotate * torque[i][0];
      omega[i][1] += dtirotate * torque[i][1];
      omega[i][2] += dtirotate * torque[i][2];
    }
}
