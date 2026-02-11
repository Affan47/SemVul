init()
{
  FixNH::init();

  if (!temperature->tempbias)
    error->all(FLERR,"Temperature for fix nvt/sllod does not have a bias");

  nondeformbias = 0;
  if (strcmp(temperature->style,"temp/deform") != 0) nondeformbias = 1;


  int i;
  for (i = 0; i < modify->nfix; i++)
    if (strcmp(modify->fix[i]->style,"deform") == 0) {
      if (((FixDeform *) modify->fix[i])->remapflag != V_REMAP)
        error->all(FLERR,"Using fix nvt/sllod with inconsistent fix deform "
                   "remap option");
      break;
    }
  if (i == modify->nfix)
    error->all(FLERR,"Using fix nvt/sllod with no fix deform defined");
}
