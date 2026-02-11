pack_bond(int **buf)
{
  int *tag = atom->tag;
  int *num_bond = atom->num_bond;
  int **bond_type = atom->bond_type;
  int **bond_atom = atom->bond_atom;
  int nlocal = atom->nlocal;
  int newton_bond = force->newton_bond;

  int i,j;
  int m = 0;
  if (newton_bond) {
    for (i = 0; i < nlocal; i++)
      for (j = 0; j < num_bond[i]; j++) {
        if (bond_type[i][j] == 0) continue;
        if (buf) {
          buf[m][0] = MAX(bond_type[i][j],-bond_type[i][j]);
          buf[m][1] = tag[i];
          buf[m][2] = bond_atom[i][j];
        }
        m++;
      }
  } else {
    for (i = 0; i < nlocal; i++)
      for (j = 0; j < num_bond[i]; j++)
        if (tag[i] < bond_atom[i][j]) {
          if (bond_type[i][j] == 0) continue;
          if (buf) {
            buf[m][0] = MAX(bond_type[i][j],-bond_type[i][j]);
            buf[m][1] = tag[i];
            buf[m][2] = bond_atom[i][j];
          }
          m++;
        }
  }

  return m;
}
