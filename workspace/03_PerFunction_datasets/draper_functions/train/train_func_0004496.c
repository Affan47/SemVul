pack_fz(int n)
{
  double **f = atom->f;

  for (int i = 0; i < nchoose; i++) {
    buf[n] = f[clist[i]][2];
    n += size_one;
  }
}
