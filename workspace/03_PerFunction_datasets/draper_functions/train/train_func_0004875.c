init()
{
  if (atom->tag_enable == 0)
    error->all(FLERR,"Cannot use fix reax/c/species unless atoms have IDs");

  reaxc = (PairReaxC *) force->pair_match("reax/c",1);
  if (reaxc == NULL) error->all(FLERR,"Cannot use fix reax/c/species without "
		  "pair_style reax/c");

  reaxc->fixspecies_flag = 1;
  nvalid = update->ntimestep+nfreq;


  int count = 0;
  for (int i = 0; i < modify->nfix; i++)
    if (strcmp(modify->fix[i]->style,"reax/c/species") == 0) count++;
  if (count > 1 && comm->me == 0)
    error->warning(FLERR,"More than one fix reax/c/species");

  if (!setupflag) {

    create_compute();


    create_fix();

    setupflag = 1;
  }

}
