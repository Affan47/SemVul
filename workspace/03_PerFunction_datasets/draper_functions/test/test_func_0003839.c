final_integrate()
{
  double dtfm,vsq,scale;

  double **v = atom->v;
  double **f = atom->f;
  double *mass = atom->mass;
  double *rmass = atom->rmass;
  int *type = atom->type;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;
  if (igroup == atom->firstgroup) nlocal = atom->nfirst;

  if (rmass) {
    for (int i = 0; i < nlocal; i++) {
      if (mask[i] & groupbit) {
        dtfm = dtf / rmass[i];
        v[i][0] += dtfm * f[i][0];
        v[i][1] += dtfm * f[i][1];
        v[i][2] += dtfm * f[i][2];

        vsq = v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2];
        if (vsq > vlimitsq) {
          ncount++;
          scale = sqrt(vlimitsq/vsq);
          v[i][0] *= scale;
          v[i][1] *= scale;
          v[i][2] *= scale;
        }
      }
    }

  } else {
    for (int i = 0; i < nlocal; i++) {
      if (mask[i] & groupbit) {
        dtfm = dtf / mass[type[i]];
        v[i][0] += dtfm * f[i][0];
        v[i][1] += dtfm * f[i][1];
        v[i][2] += dtfm * f[i][2];

        vsq = v[i][0]*v[i][0] + v[i][1]*v[i][1] + v[i][2]*v[i][2];
        if (vsq > vlimitsq) {
          ncount++;
          scale = sqrt(vlimitsq/vsq);
          v[i][0] *= scale;
          v[i][1] *= scale;
          v[i][2] *= scale;
        }
      }
    }
  }
}
