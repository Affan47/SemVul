bondfind(int i, int n1, int n2)
{
  int *tag = atom->tag;
  int **bond_atom = atom->bond_atom;
  int nbonds = atom->num_bond[i];

  int m;
  for (m = 0; m < nbonds; m++) {
    if (n1 == tag[i] && n2 == bond_atom[i][m]) break;
    if (n1 == bond_atom[i][m] && n2 == tag[i]) break;
  }
  if (m < nbonds) return m;
  return -1;
}
