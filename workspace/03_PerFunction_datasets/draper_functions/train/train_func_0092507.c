restml_makevalues()
{

  long i, j, k, l, m;
  boolean found;

  for (k = 1; k <= endsite; k++) {
    j = alias[k];
    for (i = 0; i < spp; i++) {
      for (l = 0; l <= sitelength; l++)
        curtree.nodep[i]->x2[k][l] = 1.0;
      switch (y[i][j - 1]) {

      case '+':
        for (m = 1; m <= sitelength; m++)
          curtree.nodep[i]->x2[k][m] = 0.0;
        break;

      case '-':
        curtree.nodep[i]->x2[k][0] = 0.0;
        break;

      case '?':

        break;
      }
    }
  }
  for (i = 0; i < spp; i++) {
    for (k = 1; k <= sitelength; k++)
      curtree.nodep[i]->x2[0][k] = 1.0;
    curtree.nodep[i]->x2[0][0] = 0.0;
  }
  if (trunc8)
    return;
  found = false;
  i = 1;
  while (!found && i <= endsite) {
    found = true;
    for (k = 0; k < spp; k++)
      found = (found && y[k][alias[i] - 1] == '-');
    if (!found)
      i++;
  }
  if (found) {
    weightsum += (enzymes - 1) * weight[i];
    weight[i] *= enzymes;
  }
}
