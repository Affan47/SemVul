anglefind(int i, int n1, int n2)
{
  int **angle_atom1 = atom->angle_atom1;
  int **angle_atom3 = atom->angle_atom3;
  int nangles = atom->num_angle[i];

  int m;
  for (m = 0; m < nangles; m++) {
    if (n1 == angle_atom1[i][m] && n2 == angle_atom3[i][m]) break;
    if (n1 == angle_atom3[i][m] && n2 == angle_atom1[i][m]) break;
  }
  if (m < nangles) return m;
  return -1;
}
