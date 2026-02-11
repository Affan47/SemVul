init()
{
  if (force->pair == NULL)
    error->all(FLERR,"Compute cna/atom requires a pair style be defined");
  if (sqrt(cutsq) > force->pair->cutforce)
    error->all(FLERR,"Compute cna/atom cutoff is longer than pairwise cutoff");


  if (2.0*sqrt(cutsq) > force->pair->cutforce + neighbor->skin &&
      comm->me == 0)
    error->warning(FLERR,"Compute cna/atom cutoff may be too large to find "
                   "ghost atom neighbors");

  int count = 0;
  for (int i = 0; i < modify->ncompute; i++)
    if (strcmp(modify->compute[i]->style,"cna/atom") == 0) count++;
  if (count > 1 && comm->me == 0)
    error->warning(FLERR,"More than one compute cna/atom defined");


  int irequest = neighbor->request((void *) this);
  neighbor->requests[irequest]->pair = 0;
  neighbor->requests[irequest]->compute = 1;
  neighbor->requests[irequest]->half = 0;
  neighbor->requests[irequest]->full = 1;
  neighbor->requests[irequest]->occasional = 1;
}
