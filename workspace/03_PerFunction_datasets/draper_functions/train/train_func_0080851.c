copy_arrays(int i, int j, int delflag)
{
  count[j] = count[i];
  for (int m = 0; m < count[i]; m++) extra[j][m] = extra[i][m];
}
