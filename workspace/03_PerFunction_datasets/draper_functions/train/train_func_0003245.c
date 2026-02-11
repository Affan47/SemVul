unpack_restart(int nlocal, int nth)
{
  double **extra = atom->extra;


  int m = 0;
  for (int i = 0; i < nth; i++) m += static_cast<int> (extra[nlocal][m]);
  m++;

  xoriginal[nlocal][0] = extra[nlocal][m++];
  xoriginal[nlocal][1] = extra[nlocal][m++];
  xoriginal[nlocal][2] = extra[nlocal][m++];
}
