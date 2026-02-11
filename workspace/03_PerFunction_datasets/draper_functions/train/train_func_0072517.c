pre_exchange()
{


  if (nevery && update->ntimestep < next_reneighbor) return;


  if (domain->triclinic) domain->x2lamda(atom->nlocal);
  domain->pbc();
  domain->reset_box();
  if (domain->triclinic) domain->lamda2x(atom->nlocal);


  imbnow = balance->imbalance_nlocal(maxperproc);
  if (imbnow <= thresh) {
    if (nevery) next_reneighbor = (update->ntimestep/nevery)*nevery + nevery;
    return;
  }

  rebalance();


  if (nevery) next_reneighbor = (update->ntimestep/nevery)*nevery + nevery;
}
