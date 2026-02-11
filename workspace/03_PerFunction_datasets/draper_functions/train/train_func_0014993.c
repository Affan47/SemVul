pack_ervel(int n)
{
  double *ervel = atom->ervel;

  for (int i = 0; i < nchoose; i++) {
    buf[n] = ervel[clist[i]];
    n += size_one;
  }
}
