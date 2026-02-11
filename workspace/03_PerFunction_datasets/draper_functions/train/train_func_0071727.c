scale_velocities(int t_partner, int t_me)
{
  double sfactor = sqrt(set_temp[t_partner]/set_temp[t_me]);

  double **v = atom->v;
  int nlocal = atom->nlocal;

  for (int i = 0; i < nlocal; i++) {
    v[i][0] = v[i][0]*sfactor;
    v[i][1] = v[i][1]*sfactor;
    v[i][2] = v[i][2]*sfactor;
  }
}
