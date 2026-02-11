data_bonds(int n, char *buf)
{
  int m,tmp,itype,atom1,atom2;
  char *next;
  int newton_bond = force->newton_bond;

  for (int i = 0; i < n; i++) {
    next = strchr(buf,'\n');
    *next = '\0';
    sscanf(buf,"%d %d %d %d",&tmp,&itype,&atom1,&atom2);
    if (atom1 <= 0 || atom1 > map_tag_max ||
        atom2 <= 0 || atom2 > map_tag_max)
      error->one(FLERR,"Invalid atom ID in Bonds section of data file");
    if (itype <= 0 || itype > nbondtypes)
      error->one(FLERR,"Invalid bond type in Bonds section of data file");
    if ((m = map(atom1)) >= 0) {
      bond_type[m][num_bond[m]] = itype;
      bond_atom[m][num_bond[m]] = atom2;
      num_bond[m]++;
    }
    if (newton_bond == 0) {
      if ((m = map(atom2)) >= 0) {
        bond_type[m][num_bond[m]] = itype;
        bond_atom[m][num_bond[m]] = atom1;
        num_bond[m]++;
      }
    }
    buf = next + 1;
  }
}
