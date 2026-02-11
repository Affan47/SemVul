bin_assign()
{


  if (atom->nlocal > maxatom) {
    maxatom = atom->nmax;
    memory->destroy(bin);
    memory->create(bin,maxatom,"temp/profile:bin");
  }


  double **x = atom->x;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  int ibinx,ibiny,ibinz;
  double coord;

  if (triclinic) domain->x2lamda(nlocal);

  for (int i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) {
      if (nbinx > 1) {
        coord = x[i][0];
        if (periodicity[0]) {
          if (coord < boxlo[0]) coord += prd[0];
          if (coord >= boxhi[0]) coord -= prd[0];
        }
        ibinx = static_cast<int> ((coord - boxlo[0]) * invdelta[0]);
        ibinx = MAX(ibinx,0);
        ibinx = MIN(ibinx,nbinx-1);
      } else ibinx = 0;

      if (nbiny > 1) {
        coord = x[i][1];
        if (periodicity[1]) {
          if (coord < boxlo[1]) coord += prd[1];
          if (coord >= boxhi[1]) coord -= prd[1];
        }
        ibiny = static_cast<int> ((coord - boxlo[1]) * invdelta[1]);
        ibiny = MAX(ibiny,0);
        ibiny = MIN(ibiny,nbiny-1);
      } else ibiny = 0;

      if (nbinz > 1) {
        coord = x[i][2];
        if (periodicity[2]) {
          if (coord < boxlo[2]) coord += prd[2];
          if (coord >= boxhi[2]) coord -= prd[2];
        }
        ibinz = static_cast<int> ((coord - boxlo[2]) * invdelta[2]);
        ibinz = MAX(ibinz,0);
        ibinz = MIN(ibinz,nbinz-1);
      } else ibinz = 0;

      bin[i] = nbinx*nbiny*ibinz + nbinx*ibiny + ibinx;
    }

  if (triclinic) domain->lamda2x(nlocal);
}
