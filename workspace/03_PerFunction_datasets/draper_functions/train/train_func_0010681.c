doinit()
{


  inputnumbers2seq(phylodists[0], &spp, &nonodes, 1);
  alloctree(&curtree.nodep, nonodes);
  allocd(nonodes, curtree.nodep);
  allocw(nonodes, curtree.nodep);
  if (!usertree && njumble > 1) {
    alloctree(&bestree.nodep, nonodes);
    allocd(nonodes, bestree.nodep);
    allocw(nonodes, bestree.nodep);
  }
  nayme = (naym *)Malloc(spp*sizeof(naym));
  enterorder = (long *)Malloc(spp*sizeof(long));
}
