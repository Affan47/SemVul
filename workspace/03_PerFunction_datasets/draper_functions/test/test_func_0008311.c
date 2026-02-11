write_data_section_pack(int mth, double **buf)
{
  int i;


  int *tag = atom->tag;
  int nlocal = atom->nlocal;

  for (i = 0; i < nlocal; i++) buf[i][0] = tag[i];

  for (int m = 0; m < nvalue; m++) {
    int mp1 = m+1;
    if (style[m] == MOLECULE) {
      int *molecule = atom->molecule;
      for (i = 0; i < nlocal; i++) buf[i][mp1] = molecule[i];
    } else if (style[m] == INTEGER) {
      int *vec = atom->ivector[index[m]];
      for (i = 0; i < nlocal; i++) buf[i][mp1] = vec[i];
    } else if (style[m] == DOUBLE) {
      double *vec = atom->dvector[index[m]];
      for (i = 0; i < nlocal; i++) buf[i][mp1] = vec[i];
    }
  }
}
