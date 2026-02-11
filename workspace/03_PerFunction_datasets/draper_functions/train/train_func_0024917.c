compute_peratom()
{
  invoked_peratom = update->ntimestep;


  if (atom->nlocal > nmax) {
    memory->destroy(damage);
    nmax = atom->nmax;
    memory->create(damage,nmax,"damage/atom:damage");
    vector_atom = damage;
  }


  int nlocal = atom->nlocal;
  int *mask = atom->mask;
  double *vfrac = atom->vfrac;
  double *vinter = ((FixPeriNeigh *) modify->fix[ifix_peri])->vinter;
  int **partner = ((FixPeriNeigh *) modify->fix[ifix_peri])->partner;
  int *npartner = ((FixPeriNeigh *) modify->fix[ifix_peri])->npartner;
  int i,j,jj,jnum;

  double damage_temp;

  for (i = 0; i < nlocal; i++) {
    if (mask[i] & groupbit) {
      jnum = npartner[i];
      damage_temp = 0.0;

      for (jj = 0; jj < jnum; jj++) {
        if (partner[i][jj] == 0) continue;


        j = atom->map(partner[i][jj]);
        if (j < 0) continue;

        damage_temp += vfrac[j];
      }
    }
    else damage_temp = vinter[i];

    if (vinter[i] != 0.0) damage[i] = 1.0 - damage_temp/vinter[i];
    else damage[i] = 0.0;
  }
}
