initial_integrate(int vflag)
{
  double dtfm;
  double omega[3];

  AtomVecTri::Bonus *bonus = avec->bonus;
  int *tri = atom->tri;
  double **x = atom->x;
  double **v = atom->v;
  double **f = atom->f;
  double **angmom = atom->angmom;
  double **torque = atom->torque;
  double *rmass = atom->rmass;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;
  if (igroup == atom->firstgroup) nlocal = atom->nfirst;


  dtq = 0.5 * dtv;

  for (int i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) {
      dtfm = dtf / rmass[i];
      v[i][0] += dtfm * f[i][0];
      v[i][1] += dtfm * f[i][1];
      v[i][2] += dtfm * f[i][2];
      x[i][0] += dtv * v[i][0];
      x[i][1] += dtv * v[i][1];
      x[i][2] += dtv * v[i][2];


      angmom[i][0] += dtf * torque[i][0];
      angmom[i][1] += dtf * torque[i][1];
      angmom[i][2] += dtf * torque[i][2];


      MathExtra::mq_to_omega(angmom[i],bonus[tri[i]].quat,
                             bonus[tri[i]].inertia,omega);
      MathExtra::richardson(bonus[tri[i]].quat,angmom[i],omega,
                            bonus[tri[i]].inertia,dtq);
    }
}
