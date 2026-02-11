write_data(int n, double *mybuf)
{


  int m = 0;
  for (int i = 0; i < n; i++) {
    xf[ntotal] = mybuf[m++];
    yf[ntotal] = mybuf[m++];
    zf[ntotal] = mybuf[m++];
    ntotal++;
  }


  if (ntotal == natoms) {
    write_frame();
    ntotal = 0;
  }
}
