atom2bin1d()
{
  int i,ibin;
  double *boxlo,*boxhi,*prd;
  double xremap;
  double lamda[3];

  double **x = atom->x;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  int idim = dim[0];
  int nlayerm1 = nlayers[0] - 1;
  int periodicity = domain->periodicity[idim];

  if (periodicity) {
    if (scaleflag == REDUCED) {
      boxlo = domain->boxlo_lamda;
      boxhi = domain->boxhi_lamda;
      prd = domain->prd_lamda;
    } else {
      boxlo = domain->boxlo;
      boxhi = domain->boxhi;
      prd = domain->prd;
    }
  }


  if (regionflag == 0) {
    if (scaleflag == REDUCED) domain->x2lamda(nlocal);
    for (i = 0; i < nlocal; i++)
      if (mask[i] & groupbit) {
        xremap = x[i][idim];
        if (periodicity) {
          if (xremap < boxlo[idim]) xremap += prd[idim];
          if (xremap >= boxhi[idim]) xremap -= prd[idim];
        }
        ibin = static_cast<int> ((xremap - offset[0]) * invdelta[0]);
        ibin = MAX(ibin,0);
        ibin = MIN(ibin,nlayerm1);
        bin[i] = ibin;
        count_one[ibin] += 1.0;
      }
    if (scaleflag == REDUCED) domain->lamda2x(nlocal);

  } else {
    for (i = 0; i < nlocal; i++)
      if (mask[i] & groupbit && region->match(x[i][0],x[i][1],x[i][2])) {
        if (scaleflag == REDUCED) {
          domain->x2lamda(x[i],lamda);
          xremap = lamda[idim];
        } else xremap = x[i][idim];
        if (periodicity) {
          if (xremap < boxlo[idim]) xremap += prd[idim];
          if (xremap >= boxhi[idim]) xremap -= prd[idim];
        }
        ibin = static_cast<int> ((xremap - offset[0]) * invdelta[0]);
        ibin = MAX(ibin,0);
        ibin = MIN(ibin,nlayerm1);
        bin[i] = ibin;
        count_one[ibin] += 1.0;
      }
  }
}
