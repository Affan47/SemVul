compute_vector()
{
  int i,imol;
  double dx,dy,dz,massone;
  double unwrap[3];

  invoked_array = update->ntimestep;

  molcom();

  for (i = 0; i < nmolecules; i++) rg[i] = 0.0;

  double **x = atom->x;
  int *mask = atom->mask;
  int *molecule = atom->molecule;
  int *type = atom->type;
  tagint *image = atom->image;
  double *mass = atom->mass;
  double *rmass = atom->rmass;
  int nlocal = atom->nlocal;

  for (i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) {
      imol = molecule[i];
      if (molmap) imol = molmap[imol-idlo];
      else imol--;
      domain->unmap(x[i],image[i],unwrap);
      dx = unwrap[0] - comall[imol][0];
      dy = unwrap[1] - comall[imol][1];
      dz = unwrap[2] - comall[imol][2];
      if (rmass) massone = rmass[i];
      else massone = mass[type[i]];
      rg[imol] += (dx*dx + dy*dy + dz*dz) * massone;
    }

  MPI_Allreduce(rg,vector,nmolecules,MPI_DOUBLE,MPI_SUM,world);

  for (i = 0; i < nmolecules; i++) vector[i] = sqrt(vector[i]/masstotal[i]);
}
